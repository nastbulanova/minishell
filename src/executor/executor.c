#include "../../inc/minishell.h"


void init_cmd(t_exec_data *exec_data)
{
    exec_data->cmd = NULL;
    exec_data->opt = NULL;
    exec_data->is_builtin = false;
    exec_data->redirs = NULL;
    exec_data->exit_status = 0;
}

void process_rdirs_aux(t_redir *redirs, int *safe_fd, char **redir_error)
{
    while(redirs)
    {
        errno = 0;
        if (redirs->type != HEREDOC && redirs->type != HEREDOC_QUOTED)
        {
            if (redirs->type == INPUT)
                *safe_fd = open(redirs->str, O_RDONLY);
            else if (redirs->type == OUTPUT)
                *safe_fd = open(redirs->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else if (redirs->type == OUTPUT_APPEND)
                *safe_fd = open(redirs->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (*safe_fd < 0)
            {
                if (!*redir_error)
                    *redir_error = strdup(strerror(errno));
                if (errno == 13)
                    break;
            }
            if (*safe_fd >= 0)
                close(*safe_fd);
        }
        redirs = redirs->next;
    }
}
void process_rdirs(t_exec_data *current, char **redir_error)
{
    int safe_fd;

    while (current)
    {
        process_rdirs_aux(current->redirs, &safe_fd, redir_error);
        current = current->next;
    }
}

void process_heredocs(t_exec_data *head)
{
    int heredoc_pipe[2];
    t_redir *current;

    heredoc_pipe[0] = -1;
    heredoc_pipe[1] = -1;
    current = head->redirs;
    while (current)
    {
        if (current->type == HEREDOC || current->type == HEREDOC_QUOTED)
        {
            if (heredoc_pipe[0] >= 0) 
                close(heredoc_pipe[0]);
            safe_pipe(heredoc_pipe); 
            heredoc_loop(current, heredoc_pipe[1]);
            close(heredoc_pipe[1]);
        }
        current = current->next;
    }
    if (heredoc_pipe[0] >= 0) 
        head->input_fd = heredoc_pipe[0];
}
void process_other(t_exec_data *head)
{
    int safe_fd_input;
    int safe_fd_output;
    t_redir *current;
       
    safe_fd_input = -1;
    safe_fd_output = -1;
    current = head->redirs; 
    while (current && !current->error)
    {
        if (current->type != HEREDOC && current->type != HEREDOC_QUOTED)
        {
            errno = 0;
            if (current->type == INPUT)
            {
                if (safe_fd_input >= 0)
                    close(safe_fd_input);
                safe_fd_input = open(current->str, O_RDONLY);
                if (safe_fd_input < 0)
                    current->error = ft_strdup(strerror(errno));//we save the error message and keep it because we wont process anything else on this command (including output redirects)
            }
            else
            {
                if (safe_fd_output >= 0)
                    close(safe_fd_output);
                if (current->type == OUTPUT_APPEND)
                    safe_fd_output = open(current->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
                else if (current->type == OUTPUT)
                    safe_fd_output = open(current->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (safe_fd_output < 0)
                    current->error = ft_strdup(strerror(errno));//we save the error message and keep it because we wont process anything else on this command (including output redirects)
            }
        }
        current = current->next;
    }
    if (current->error)
    {
        if (safe_fd_input >= 0)
            close(safe_fd_input);
        if (safe_fd_output >= 0)
            close(safe_fd_output);
        close(head->outpipe[0]);//close the pipe on error
        close(head->outpipe[1]);//close the pipe on error
    }
    else
    {
        if (safe_fd_input >= 0 && !has_heredoc(head->redirs))//if we have a valid input_fd and no heredoc this will be our input
            head->input_fd = safe_fd_input;
        if (safe_fd_output >= 0)//if we have an output file then thats the output, we care nothing about the next command
        {
            head->outpipe[1] = safe_fd_output;//we assing this output pipe to the file
            close(head->outpipe[0]);//we close the read end because we wont use it
        }
    }
}
void process_redirs(t_exec_data *head)
{
    while (head)
    {
        if (head->next)
            safe_pipe(head->outpipe);
        //create an output pipe right away (this will allways be need either by an output file or by the STDOUT)
        process_heredocs(head);
        process_other(head);
        head = head->next;
    }
}
void execute_command_list(t_exec_data *head, char **envp)
{
    process_redirs(head);
    process_commands(head, envp);
    free_exec_data_list(head);
}
void execute_command(t_exec_data *head, char **envp)
{
    t_exec_data *current;
    t_pid_list *pid_list;
    pid_t pid;
    int original_fd = dup(STDIN_FILENO);
    int prev_fd[2] = {dup(STDIN_FILENO), -1};

    current = head;
    pid_list = NULL;
    while (current)
    {
        //fprintf(stderr, "Current CMD: %s CPipe[%d][%d] Prev_fd[%d]\n", current->cmd, current->outpipe[0], current->outpipe[1], prev_fd);
        //the safe_ function all have error checks and exit minishell gracefully is an error occurs (like malloc, dup2, pipe and other general errors)
        safe_pipe(current->inpipe); //allways create a pipe for the input, if there are input redirects use the last valid one, else use STDIN
        if (current->next)
           safe_pipe(current->outpipe); // only create pipe if theres a valid outfile or if theres a next command
        //process all command list redirects
        pid = safe_fork();
        add_pid(&pid_list, pid);
        //fprintf(stderr, "Current CMD: %s CPipe[%d][%d] Prev_fd[%d]\n", current->cmd, current->outpipe[0], current->outpipe[1], prev_fd);
            fprintf(stderr, "Current CMD: %s InPipe[%d][%d], OutPipe[%d][%d] Prev_fd[%d]\n", current->cmd, current->inpipe[0], current->inpipe[1], current->outpipe[0], current->outpipe[1], prev_fd[0]);
        if (pid == 0)
        {
            if (prev_fd[0] >= 0)
            {
                current->inpipe[0] = prev_fd[0];
            }
            safe_dup_two(current->inpipe[0], STDIN_FILENO);
            close(current->inpipe[1]);
            if (current->next) // or if there is a output redirect
            {
                safe_dup_two(current->outpipe[1], STDOUT_FILENO);  
                close(current->outpipe[0]);
            }
            if (execve(current->cmd, current->opt, envp) == -1)
            {
                perror("execve failed");
                perror(strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            close(current->outpipe[1]);
            if (prev_fd[0] >= 0)
                close(prev_fd[0]);
            if (prev_fd[1] >= 0)
                close(prev_fd[1]);
            //close(current->inpipe[0]);
            //close(current->inpipe[1]);
            prev_fd[0] = current->outpipe[0];
            prev_fd[1] = current->outpipe[0];
        }
        current = current->next;
    }
    t_pid_list *temp = pid_list;
    while (temp)
    {
        waitpid(temp->pid, NULL, 0);
        temp = temp->next;
    }
    dup2(original_fd, STDIN_FILENO);
}
