#include "../../inc/minishell.h"

static void process_io_output(t_exec_data *cmd, t_redir *current, int *temp_output_fd)
{
    int flags;

    close_fd(temp_output_fd);
    if (current->type == OUTPUT)
        flags = (O_WRONLY | O_CREAT | O_TRUNC);
    else
        flags = (O_WRONLY | O_CREAT | O_APPEND);
    *temp_output_fd = open(current->str, flags, 0644);
    if (*temp_output_fd < 0)
    {
        current->error =  built_error_string(current->str, strerror(errno));
        //if (errno == EACCES)
        //    cmd->exit_status = 126;
        //else if (errno == ENOENT)
        //    cmd->exit_status = 127; //(1)
        //else
        cmd->exit_status = 1;
    }
}

static void process_io_input(t_exec_data *cmd, t_redir *current, int *temp_input_fd)
{
    close_fd(temp_input_fd);
    *temp_input_fd = open(current->str, O_RDONLY);
    if (*temp_input_fd < 0)
    {
       
        current->error =  built_error_string(current->str, strerror(errno));
        //if (errno == EACCES)
        //    cmd->exit_status = 126;
        //else if (errno == ENOENT)
        //    cmd->exit_status = 127;
        //else
        cmd->exit_status = 1;
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
        if (current->type == INPUT)
            process_io_input(cmd, current, &temp_input_fd);
        else if (current->type == OUTPUT || current->type == OUTPUT_APPEND)
            process_io_output(cmd, current, &temp_output_fd);
        error_msg = current->error;
        current = current->next;
    }
    if (!current || !current->error)
    {
        cmd->input_fd = temp_input_fd;
        cmd->output_fd = temp_output_fd;
    }
    else
    {
        close_fd(&temp_input_fd);
        close_fd(&temp_output_fd);
    }
}

void handle_heredoc_redirection(t_minishell *data, t_exec_data *head)
{
    t_redir *current;
   
    current = head->redirs;
    while (current && data->exit_code != 130)
    {
        if (current->type == HEREDOC || current->type == HEREDOC_QUOTED)
        {
            close_fd(&data->heredoc_pipe[0]);
            safe_pipe(data->heredoc_pipe); 
            heredoc_loop(current, data->heredoc_pipe[1]);
            close_fd(&data->heredoc_pipe[1]);
            if (data->exit_code == 130)
                close_fd(&data->heredoc_pipe[0]);    
        }
        current = current->next;
    }
    if (data->heredoc_pipe[0] >= 0) 
        head->input_fd = data->heredoc_pipe[0];
}
