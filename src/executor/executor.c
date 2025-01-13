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

void execute_command_single(t_exec_data *current, char **envp, bool is_parent)
{
    if (current->is_builtin)
    { 
        if (!is_parent)
            exit(call_builtin(current));
        else
            call_builtin(current); 
    }
    else
    {
        if (execve(current->cmd, current->opt, envp) == -1)
        {
            perror("execve failed");
            perror(strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
}
void execute_child(t_exec_data *current, int* previous_pipe, char* redir_error, char **envp)
{
    if (previous_pipe[0] >= 0)
    {
        dup2(previous_pipe[0], STDIN_FILENO);
        close(previous_pipe[0]);
    }              
    if (current->pipe[1] >= 0 && (current->next || has_output(current->redirs)))
    {
        if (dup2(current->pipe[1], STDOUT_FILENO) == -1) 
        {
            perror("dup2 failed");
        }
        close(current->pipe[1]); 
    }   
    if (redir_error)
    {
        //fprintf(stderr, "Redir Error %s\n",  redir_error);
        free(redir_error);
        redir_error = NULL;
        exit(EXIT_FAILURE);
    }
    if (!current->is_builtin && access(current->cmd, F_OK) != 0)
    {
        fprintf(stderr, "Minishell: command not found: %s\n", current->cmd);
        exit(EXIT_FAILURE);
    }
    execute_command_single(current, envp, false);
}
void execute_command_chain(t_exec_data *current, int* previous_pipe, char* redir_error, char **envp)
{
     pid_t pid;

     while (current)
     {
        printf("Current CMD: %s\n", current->cmd);
        if (!init_pipe(current->pipe))
            break;
        if (setup_stdin(current, previous_pipe, redir_error) && setup_stdout(current, redir_error))
        {
            printf("setup_stdin &&  setup_stdout return true\n");
            set_state_signal_handlers(CHILD);
            pid = fork();
             if (pid == 0)
                execute_child(current, previous_pipe, redir_error, envp);
             else
             {
                set_state_signal_handlers(MAIN);
                waitpid(pid,NULL, 0);
                manage_pipes(current, previous_pipe);
             }
        }
        else
            manage_pipes(current, previous_pipe);
        current = current->next;
     }
     
}

void execute_command(t_exec_data *list_exec_data, char **envp)
{
    int previous_pipe[2] = {-1, -1};
    t_exec_data *current;
    char *redir_error;
    bool output_exists;

    current = list_exec_data;
    redir_error = NULL;
    process_rdirs(current, &redir_error);
    if (!current->next && current->is_builtin)
    {
        output_exists = has_output(current->redirs);
        if (output_exists && setup_single_pipe(current, previous_pipe))  
            execute_command_single(current, envp, true);
        if (output_exists && restore_single_pipe(previous_pipe))
            return ;
    }
    else
        execute_command_chain(current, previous_pipe, redir_error, envp);
    if (redir_error)
        free(redir_error);
    if (previous_pipe[0] >= 0)
        close_pipe(previous_pipe);
    free_array(envp, NULL);
}
