#include "../../inc/minishell.h"



static void print_and_cleanup_error(t_exec_data *cmd, char *final_string)
{
    ft_putendl_fd(final_string, STDERR_FILENO);
    free(final_string);
    close_fd(&cmd->input_fd);
    close_fd(&cmd->output_fd);
}

static bool command_is_valid_aux(t_minishell *data, t_exec_data *cmd, char **final_string)
{
    if (access(cmd->cmd, F_OK) == -1)
    {
        data->exit_code = 127;
        if (errno == ENOENT)
            *final_string = built_error_string(cmd->cmd, strerror(errno));
        return (false);
    }
    if (access(cmd->cmd, X_OK) == -1)
    {
        data->exit_code = 126;
        *final_string = built_error_string(cmd->cmd, strerror(errno));
        return (false);
    }
    return (true);
}

bool command_is_valid(t_exec_data *cmd, t_minishell *data)
{
    char *error;
    char *final_string;
    bool result;

    result = true;
    if (cmd->exit_status != 0)
    {
        data->exit_code = cmd->exit_status;
        error = get_rdir_error(cmd->redirs);
        final_string = built_error_string(cmd->cmd, error);
        result = false;
    }
    if (result && !cmd->is_builtin)
        result = command_is_valid_aux(data, cmd, &final_string);
    if (!result)
        print_and_cleanup_error(cmd, final_string);
    return (result);
}

static void execute_pipe(t_minishell *data, t_exec_data *head, char** envp)
{
    t_exec_data *current;
    t_exec_data *previous;
    t_pid_list *pid_list;
    pid_t       pid;

    current = head;
    pid_list = NULL;
    previous = NULL;
    while (current)
    {
        if (command_is_valid(current, data))
        {
            if (current->next)
                safe_pipe(current->outpipe);    
            pid = safe_fork();
            if (pid == 0)
                handle_child(current, previous, envp);    
            else
                handle_parent(current, previous, &pid_list, pid);
        }
        close_command_fds(previous);
        previous = current;
        current = current->next;
    }
    handle_exit_status(data, pid_list);
}

void execute_command_list(t_minishell *data, t_exec_data *head, char **envp)
{
    t_exec_data *current;

    current = head;
    while (current)
    {
        handle_heredoc_redirection (data, current);
        if (data->exit_code == 130)
            return;
        handle_io_redirections(current);
        current = current->next;
    }
    if (data->exit_code == 130)
        return;
    if (!head->next)
        execute_non_pipe(data, head, envp);
    else
        execute_pipe(data, head, envp);

}

