#include "../../inc/minishell.h"

void heredoc_loop(const char *terminator, int fd)
{
    char * input;
    while (true)
    {
        input = readline("> ");
        if (!input) 
        {
            write(fd, "\n", 1);
            break;
        }
        if (strcmp(input, terminator) == 0)
        {
            free(input);
            break;
        }
        write(fd, input, strlen(input));
        write(fd, "\n", 1);
        free(input);
    }
}

bool setup_in_out(t_extended_exec_data *current, int *previous_pipe, int *current_pipe)
{
    errno = 0;
    if (current->infile)
    {
        previous_pipe[0] = open(current->infile, O_RDONLY);
        if (previous_pipe[0] < 0) 
            return (fd_open_failure(current->infile, strerror(errno)));
    }
    else if (current->here_doc_terminator)
    {
        if (previous_pipe[1] < 0 && pipe(previous_pipe) != 0)
            return (pipe_open_failure("failed to open heredoc pipe"));
        //set_state_signal_handlers(HERE_DOC);
        heredoc_loop(current->here_doc_terminator, previous_pipe[1]);
    }
    if (current->outfile)
    {
        if (current->append_output)
            current_pipe[1] = open(current->outfile, O_APPEND);
        else
            current_pipe[1] = open(current->outfile, O_WRONLY);
         if (current_pipe[1] < 0) 
            return (fd_open_failure(current->outfile, strerror(errno)));
    }
    return (true);
}
int process_builtin(t_extended_exec_data *current, t_minishell *data)
{
        if (c_strcmp(current->cmd, "echo"))
            return (cmd_echo(current->opt, data));
        else if (c_strcmp(current->cmd, "cd"))
            return (cmd_cd(current->opt, data));
        else if (c_strcmp(current->cmd, "env"))
            return (cmd_env(current->opt, data));
        else if (c_strcmp(current->cmd, "exit"))
            return (cmd_exit(current->opt, data));
        else if (c_strcmp(current->cmd, "export"))
            return (cmd_export(current->opt, data));
        else if (c_strcmp(current->cmd, "pwd"))
            return (cmd_pwd(data));
        else if (c_strcmp(current->cmd, "unset"))
            return (cmd_unset(current->opt, data));
        else
            return (0);
}

void process_pid(pid_t pid, t_extended_exec_data *current, int *previous_pipe, t_minishell *data)
{
    (void)data;
    if (pid == 0)
    {
        if (previous_pipe[0] >= 0) 
            dup2(previous_pipe[0], STDIN_FILENO);
        if (current->next || current->outfile)
        {
            if (current->pipe[1] >= 0)
                dup2(current->pipe[1], STDOUT_FILENO);
        }
        close_pipe(previous_pipe);
        //if (current->is_builtin)
        //    current->exit_status = process_builtin(current, data);
        //else
            current->exit_status = execve(current->cmd, current->opt, current->env);
    }
    else
    {
        //set_state_signal_handlers(MAIN);
        close_pipe(previous_pipe);
        previous_pipe[0] = current->pipe[0];
        previous_pipe[1] = current->pipe[1];  
    }
}
void setup_stdin(t_extended_exec_data *current, int *pipe_fd)
{
    if (current->infile)
    {
        errno = 0;
        pipe_fd[0] = open(current->infile, O_RDONLY);
        if (pipe_fd[0] < 0) {
            fprintf(stderr, "Minishell: ");
            fprintf(stderr, "%s", strerror(errno));
            fprintf(stderr, ": %s\n", current->infile);
            exit(EXIT_FAILURE);
        }
    }
    else if (current->here_doc_terminator)
    {
        if (pipe_fd[1] < 0 && pipe(pipe_fd) != 0)
        {
            fprintf(stderr, "failed to open heredoc pipe (%d: %s)\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
        heredoc_loop(current->here_doc_terminator, pipe_fd[1]);
    }
}

void setup_stdout(t_extended_exec_data *current, int *pipe_fd)
{
    if (current->outfile)
    {
        errno = 0;
        if (current->append_output)
            pipe_fd[1] = open(current->outfile, O_APPEND);
        else
            pipe_fd[1] = open(current->outfile, O_WRONLY);
         if (pipe_fd[1] < 0) 
         {
            fprintf(stderr, "Minishell: ");
            fprintf(stderr, "%s", strerror(errno));
            fprintf(stderr, ": %s\n", current->outfile);
            exit(EXIT_FAILURE); 
        }
    }
}



void process_parent(int *pipe_fd, t_extended_exec_data *current)
{
    close_pipe(pipe_fd);
    pipe_fd[0] = current->pipe[0];
    pipe_fd[1] = current->pipe[1];  

}

void process_child(t_extended_exec_data *current, int *pipe_fd)
{
    if (pipe_fd[0] >= 0) 
        dup2(pipe_fd[0], STDIN_FILENO);
    if (current->next || current->outfile)
    {
        if (current->pipe[1] >= 0)
            dup2(current->pipe[1], STDOUT_FILENO);
    }
    close_pipe(pipe_fd);
    //printf("current->opt\n");
    //print_array(current->opt);
    //printf("current->env\n");
    //print_array(current->env);
    current->exit_status = execve(current->cmd, current->opt, current->env);
    if (current->exit_status == -1) 
    {
        perror("Error executing command");
        exit(EXIT_FAILURE);
    }
}
void execute_command(t_extended_exec_data *exec_data, t_minishell *data)
{
    (void)data;
    int previous_pipe[2] = {-1, -1};
    pid_t pid;
    t_extended_exec_data *current;

    current = exec_data;
    while (current && current->cmd)
    {
        if (pipe(current->pipe) != 0)
        {
            fprintf(stderr, "failed to open current pipe (%d: %s)\n", errno, strerror(errno));
            exit(EXIT_FAILURE);
        }
        //setup heredoc signals
        setup_stdin(current, previous_pipe);   
        setup_stdout(current, current->pipe);
        //setup signals
        pid = fork();
        if (pid == 0)
            process_child(current, previous_pipe);
        else
            process_parent(previous_pipe, current);
        current = current->next;
    }
    close_pipe(previous_pipe);
}
