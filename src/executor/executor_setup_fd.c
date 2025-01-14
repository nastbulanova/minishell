#include "../../inc/minishell.h"


static void setup_stdin_aux(t_redir *temp, int* previous_pipe, int safe_fd)
{
    if (is_last_input(temp))
    {
        previous_pipe[0] = safe_fd;
        close(previous_pipe[1]);
    }
    else 
    {
        close(safe_fd);
    }
}

bool setup_stdin(t_exec_data *current, int* previous_pipe, char* redir_error)
{
    int safe_fd;
    t_redir *temp;

    temp = current->redirs;
    if (previous_pipe[1] < 0 && has_input(temp))
        init_pipe(previous_pipe);
    while (temp)
    {
        if (temp->type == HEREDOC || temp->type == HEREDOC_QUOTED)
            heredoc_loop(temp, previous_pipe[1]);
        else if(temp->type == INPUT)
        {
            errno = 0;
            safe_fd = open(temp->str, O_RDONLY);
            if (safe_fd < 0)
            {
                if(previous_pipe[1] >= 0)
                    close(previous_pipe[1]);
                return (safe_fd_error(temp, redir_error, errno));
            }
            setup_stdin_aux(temp, previous_pipe, safe_fd);
        }
        temp = temp->next;
    }
    return (true);
}

static void setup_stdout_aux(t_redir *temp, int *safe_fd)
{
    if (*safe_fd >= 0)
        close(*safe_fd);
    errno = 0;
    if (temp->type == OUTPUT_APPEND)
        *safe_fd = open(temp->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else
        *safe_fd = open(temp->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
}

bool setup_stdout(t_exec_data *current, char* redir_error)
{
    int safe_fd;
    t_redir *temp;

    safe_fd = -1;
    temp = current->redirs;
    if (has_output(current->redirs))
    {
        if (current->pipe[1] >= 0)
                close(current->pipe[1]);
    }
    while (temp)
    {
        if (temp->type == OUTPUT || temp->type == OUTPUT_APPEND)
        {
            setup_stdout_aux(temp, &safe_fd);
            if (safe_fd < 0) 
                return (safe_fd_error_aux(temp, redir_error, errno));
            current->pipe[1] = safe_fd;
        }
        temp = temp->next;
    }
    return (true);
}
