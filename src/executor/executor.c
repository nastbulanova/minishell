#include "../../inc/minishell.h"


void init_cmd(t_exec_data *exec_data)
{
    exec_data->cmd = NULL;
    exec_data->opt = NULL;
    exec_data->is_builtin = false;
    exec_data->redirs = NULL;
    exec_data->exit_status = 0;
    exec_data->input_fd = -1;
    exec_data->output_fd = -1;
    exec_data->outpipe[0] = -1;
    exec_data->outpipe[1] = -1;
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
    t_redir *current;
    char *str_error;

    int local_input;
    int local_output;
    str_error = NULL;
    local_input = -1;
    local_output = -1;
    current = head->redirs; 
    while (current && !current->error)
    {
        if (current->type != HEREDOC && current->type != HEREDOC_QUOTED)
        {
            errno = 0;
            if (current->type == INPUT)
            {
                if (local_input >= 0)
                    close(local_input);
                local_input = open(current->str, O_RDONLY);
                if (local_input < 0)
                    current->error = ft_strdup(strerror(errno));//we save the error message and keep it because we wont process anything else on this command (including output redirects)
            }
            else
            {
                if (local_output >= 0)
                    close(local_output);
                if (current->type == OUTPUT_APPEND)
                    local_output = open(current->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
                else if (current->type == OUTPUT)
                    local_output = open(current->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (local_output < 0)
                {
                    current->error = ft_strdup(strerror(errno));//we save the error message and keep it because we wont process anything else on this command (including output redirects)
                    str_error = current->error;
                }
            }
        }
        current = current->next;
    }
    if (str_error)
    {
        if (local_input >= 0)
            close(local_input);
        if (local_output >= 0)
            close(local_output);
    }
    else
    {
        if (local_input >= 0 && !has_heredoc(head->redirs))//if we have a valid input_fd and no heredoc this will be our input
            head->input_fd = local_input;
        else if(local_input >= 0)
            close(local_input);
        if (local_output >= 0)
            head->output_fd = local_output;
    }
}
void process_commands(t_exec_data *head, char **envp)
{
    t_exec_data *current = head;
    t_pid_list *pid_list;
    pid_t       pid;

    (void)envp;
    pid_list = NULL;
    current->input_fd = -1;
    current->output_fd = -1;
    while (current)
    {

        safe_pipe(current->outpipe);
        pid = fork();
        if (pid == 0)
        {
            if (current->input_fd < 0)
                current->input_fd = dup(STDIN_FILENO);
            fprintf(stderr, "\nCurrent CMD:%s\nStarting Pipe[%d][%d] InputFD: %d, OutputFD:%d\n", current->cmd, current->outpipe[0], current->outpipe[1], current->input_fd, current->output_fd);
            if (current->input_fd >= 0)
            {
                fprintf(stderr, "current->input_fd >= 0 (%d) STDIN_FILENO\n", current->input_fd);
                safe_dup_two(current->input_fd, STDIN_FILENO);
                close(current->input_fd);
            }
            if(current->next)
            {
                fprintf(stderr, "current->outpipe[1] (%d) STDOUT_FILENO\n", current->outpipe[1]);
                safe_dup_two(current->outpipe[1], STDOUT_FILENO);
                close(current->outpipe[1]);
            }
            close(current->outpipe[0]);
            close(current->output_fd);
            if (execve(current->cmd, current->opt, envp) == -1)
            {
                perror("execve failed");
                perror(strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        else // PARENT
        {
            //fprinf(stderr, "Parent PID %d\n", pid);
            add_pid(&pid_list, pid);
            close(current->outpipe[1]);
            if (current->input_fd >= 0)
                close(current->input_fd);
            if (current->next)
                current->next->input_fd = current->outpipe[0];
        }
        current = current->next;
    }
    while(pid_list)
    {
        waitpid(pid_list->pid, NULL, 0);
        pid_list = pid_list->next;
    }
    
}
void process_redirs(t_exec_data *head)
{
    while (head)
    {
        process_heredocs(head);
        process_other(head);
        head = head->next;
    }
}
void execute_command_list(t_exec_data *head, char **envp)
{
    process_redirs(head);
    process_commands(head, envp);
    
}

