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
    //fprintf(stderr, "command_is_valid_aux HIT\n");
    if (access(cmd->cmd, F_OK) == -1)
    {
        data->exit_code = 127;
        if (errno == ENOENT)
            *final_string = built_error_string(cmd->cmd, "command not found", false);
        return (false);
    } else if (access(cmd->cmd, X_OK) == -1)
    {
        data->exit_code = 126;
        *final_string = built_error_string(cmd->cmd, strerror(errno), true);
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
        final_string = ft_strdup(error);
        result = false;
    }
    if (result && !cmd->is_builtin)
        result = command_is_valid_aux(data, cmd, &final_string);
    if (!result)
        print_and_cleanup_error(cmd, final_string);
    
    return (result);
}

void execute_pipe(t_minishell *data, t_exec_data *head, char** envp)
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
            if (current->next)
                safe_pipe(current->outpipe);    
            pid = fork();
            if (pid < 0)
            {
                free_pid_list(&pid_list);
                return;
            }
            if (pid == 0)
                handle_child(current, previous, envp, head);    
            else
                handle_parent(current, previous, &pid_list, pid);
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
            break;
        handle_io_redirections(current);
        //fprintf(stderr, "CMD %s After redirection  input_fd %d, output_fd %d, outpit[%d][%d]\n", head->cmd, head->input_fd, head->output_fd, head->outpipe[0], head->outpipe[1]);
        current = current->next;
    }
    if (data->exit_code == 130)
        return;
    if (!head->next)
        execute_non_pipe(data, head, envp);
    else
        execute_pipe(data, head, envp);

    free_array(envp, NULL);
}

