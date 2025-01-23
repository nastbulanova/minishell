#include "../../inc/minishell.h"

void close_fd(int *fd)
{
    if (fd && *fd >=0)
    {
        if (close(*fd) == -1)
            minishell_exit("Failed to close file descriptor.", 2, STDERR_FILENO);   
        *fd = -1;
    }
}

void close_pipe(int pipe_fd[2])
{
    close_fd(&pipe_fd[0]);
    close_fd(&pipe_fd[1]); 
}

void safe_pipe(int pipe_fd[2])
{
    if (pipe(pipe_fd) != 0)
        minishell_exit("pipe failure @ safe_pipe", 2, STDERR_FILENO);
}

void safe_dup_two(int fd, int fd_two)
{   errno = 0;
    if(dup2(fd, fd_two) == -1)
        minishell_exit("dup2 error on safe_dup_two\n", 1, STDERR_FILENO);
}

pid_t safe_fork()
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        minishell_exit("failed fork @ safe_fork (executor_pid)", 1, STDERR_FILENO); 
    return (pid);
}



