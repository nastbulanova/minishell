#include "../../inc/minishell.h"

static void heredoc_loop(const char *terminator, int fd)
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

static bool setup_in_out(t_extended_exec_data *current, int *previous_pipe, int *current_pipe)
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
        set_state_signal_handlers(HERE_DOC);
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
static int process_builtin(t_extended_exec_data *current, t_minishell *data)
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

static void process_pid(pid_t pid, t_extended_exec_data *current, int *previous_pipe, t_minishell *data)
{
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
        if (current->is_builtin)
            current->exit_status = process_builtin(current, data);
        else
            current->exit_status = execve(current->cmd, current->opt, current->env);
    }
    else
    {
        set_state_signal_handlers(MAIN);
        close_pipe(previous_pipe);
        previous_pipe[0] = current->pipe[0];
        previous_pipe[1] = current->pipe[1];  
    }
    return (true);
}
void execute_command(t_extended_exec_data *exec_data, t_minishell *data)
{
    int previous_pipe[2] = {-1, -1};
    pid_t pid;
    t_extended_exec_data *current;

    current = exec_data;
    while (current && current->cmd)
    {
        if (!pipe_init(current->pipe))
            break;
        if (!setup_in_out(current, previous_pipe, current->pipe))
            break;
        set_state_signal_handlers(CHILD);
        pid = fork();
        process_pid(pid, current, previous_pipe, data);
        data->exit_code = current->exit_status;
        current = current->next;
    }
    close_pipe(previous_pipe);
}
