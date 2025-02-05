#include "../../inc/minishell.h"

bool close_fd(int *fd)
{
    if (fd && *fd >=0)
    {
        if (close(*fd) == -1)
        {
            //minishell_exit("Failed to close file descriptor.", 2, STDERR_FILENO, false);  
            ft_putstr_fd("Failed to close file descriptor.\n", STDERR_FILENO);
            return (false);
        }
        *fd = -1;
        return (true);
    }
    return (true);
}

bool close_pipe(int pipe_fd[2])
{
    return (close_fd(&pipe_fd[0]) && close_fd(&pipe_fd[1])); 
}

bool safe_pipe(int pipe_fd[2])
{
    if (pipe(pipe_fd) != 0)
    {
        //minishell_exit("pipe failure @ safe_pipe", 2, STDERR_FILENO, false);
        ft_putstr_fd("Failed to create pipe.\n", STDERR_FILENO);
        return (false);
    }
    return (true);
}

bool safe_dup_two(int fd, int fd_two)
{   
    if(dup2(fd, fd_two) == -1)
    {
        //minishell_exit("dup2 error on safe_dup_two\n", 2, STDERR_FILENO, false);
        ft_putstr_fd("dup2 error.\n", STDERR_FILENO);
        return (false);
    }
    return (true);
}





