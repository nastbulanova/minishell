#include "../../inc/minishell.h"

static void process_io_output(t_exec_data *cmd, t_redir *current, int *temp_output_fd)
{
    int flags;

    close_fd(temp_output_fd);
    if (current->type == OUTPUT)
        flags = (O_WRONLY | O_CREAT | O_TRUNC);
    else
        flags = (O_WRONLY | O_CREAT | O_APPEND);
    errno = 0;
    *temp_output_fd = open(current->str, flags, 0644);
    if (*temp_output_fd < 0)
    {
        if (errno == ENOENT)
        {
            cmd->exit_status = 127;
            current->error = built_error_string(current->str, "No such file or directory", false);
        }
        else if (errno == EACCES)
        {
            cmd->exit_status = 126;
            current->error = built_error_string(current->str, "Permission denied", false);
        }
        else
        {
            cmd->exit_status = 1;
            current->error = built_error_string(current->str, "Unknown error", false);
        }
    }
}

static void process_io_input(t_exec_data *cmd, t_redir *current, int *temp_input_fd)
{
    close_fd(temp_input_fd);
    *temp_input_fd = open(current->str, O_RDONLY);
    if (*temp_input_fd < 0)
    {
        if (errno == ENOENT)
        {
            cmd->exit_status = 127;
            current->error = built_error_string(current->str, "No such file or directory", false);
        }
        else if (errno == EACCES)
        {
            cmd->exit_status = 126;
            current->error = built_error_string(current->str, "Permission denied", false);
        }
        else
        {
            cmd->exit_status = 1;
            current->error = built_error_string(current->str, "Unknown error", false);
        }
    }
}

static void finalize_redirections(t_exec_data *cmd, char *error_msg, int *temp_input_fd, int *temp_output_fd)
{
    if (!error_msg)
    {
        if (*temp_input_fd >= 0)
        {
            if (cmd->input_fd >= 0)
                close_fd(&cmd->input_fd);
            cmd->input_fd = *temp_input_fd;
        }
        cmd->output_fd = *temp_output_fd;
    }
    else
    {
        close_fd(temp_input_fd);
        close_fd(temp_output_fd);
    }
}

void handle_io_redirections(t_exec_data *cmd)
{
    t_redir *current;
    int temp_input_fd;
    int temp_output_fd;
    char *error_msg;

    error_msg = NULL;
    temp_input_fd = -1;
    temp_output_fd = -1;
    current = cmd->redirs;
    while (current && !error_msg)
    {
        if (current->str[0] == '$')
        {
            current->error =  built_error_string(current->str, "ambiguous redirect", true);
            cmd->exit_status = 1;
        }
        else if (current->type == INPUT)
            process_io_input(cmd, current, &temp_input_fd);
        else if (current->type == OUTPUT || current->type == OUTPUT_APPEND)
            process_io_output(cmd, current, &temp_output_fd);
        error_msg = current->error;
        
        current = current->next;
    }
    finalize_redirections(cmd, error_msg, &temp_input_fd, &temp_output_fd);
}

void handle_heredoc_redirection(t_minishell *data, t_exec_data *head)
{
    t_redir *current;
   
    current = head->redirs;
    while (current && data->exit_code != 130)
    {
        if (current->type == HEREDOC || current->type == HEREDOC_QUOTED)
        {
            close_pipe(data->heredoc_pipe);
            safe_pipe(data->heredoc_pipe); 
            heredoc_loop(current, data->heredoc_pipe[1]);
            close_fd(&data->heredoc_pipe[1]);
            if (data->exit_code == 130)
                close_fd(&data->heredoc_pipe[0]);    
        }
        current = current->next;
    }
    if (data->heredoc_pipe[0] >= 0) 
    {
        head->input_fd = data->heredoc_pipe[0];
        data->heredoc_pipe[0] = -1;
        data->heredoc_pipe[1] = -1;
    }
}
