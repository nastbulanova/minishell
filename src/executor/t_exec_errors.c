#include "../../inc/minishell.h"
bool fd_open_failure(char *file, char *err_str)
{
    ft_putstr_fd("Minishell: ", STDERR_FILENO);
    ft_putstr_fd(err_str,  STDERR_FILENO);
    ft_putstr_fd(": ", STDERR_FILENO);
    ft_putendl_fd(file, STDERR_FILENO);
    return (false);
}

bool pipe_open_failure(char *msg)
{
    ft_putstr_fd("Minishell: ", STDERR_FILENO);
    ft_putendl_fd(msg,  STDERR_FILENO);
    return (false);
}

bool pipe_init(int *pipe_fd)
{
    if (pipe(pipe_fd) != 0)
    {
        ft_putstr_fd("Minishell: ", STDERR_FILENO);
        ft_putendl_fd(strerror(errno),  STDERR_FILENO);
        return (false);
    }
    return (true);
}


