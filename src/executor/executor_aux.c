#include "../../inc/minishell.h"

bool has_heredoc(t_redir *redir)
{
    if (!redir)
        return (false);

    while (redir)
    {
        if (redir->type == HEREDOC
        || redir->type == HEREDOC_QUOTED)
            return (true);
        redir = redir->next;
    }
    return (false);
}

bool has_input(t_redir *redir)
{
    if (!redir)
        return (false);

    while (redir)
    {
        if (redir->type == INPUT
        || redir->type == HEREDOC
        || redir->type == HEREDOC_QUOTED)
            return (true);
        redir = redir->next;
    }
    return (false);
}

bool has_output(t_redir *redir)
{
    if (!redir)
        return (false);

    while (redir)
    {
        if (redir->type == OUTPUT || redir->type == OUTPUT_APPEND)
            return (true);
        redir = redir->next;
    }
    return (false);
}

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

