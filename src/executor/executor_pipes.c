#include "../../inc/minishell.h"

void close_pipe(int *pipe_fd)
{
    if (pipe_fd[0] >= 0) 
        close(pipe_fd[0]);
    if (pipe_fd[1] >= 0) 
        close(pipe_fd[1]); 
}

bool init_pipe(int *pipe_fd)
{
    if (pipe(pipe_fd) != 0)
    {
        fprintf(stderr, "failed to open current pipe (%d: %s)\n", errno, strerror(errno));
        return (false);
    }
    return (true);
}

bool restore_single_pipe(int *previous_pipe)
{
    if (dup2(previous_pipe[1], STDOUT_FILENO) == -1) 
    {
        perror("dup2 restore failed");
        close(previous_pipe[1]);
        return (false);
    }
    close(previous_pipe[1]);
    return (true);
}

bool setup_single_pipe(t_exec_data *current, int *previous_pipe)
{
    if (!init_pipe(current->pipe))
        return (false);
    previous_pipe[1] = dup(STDOUT_FILENO);
    if (dup2(current->pipe[1], STDOUT_FILENO) == -1) 
    {
        perror("dup2 failed");
        close(previous_pipe[1]);
        return (false);
    }
    return (true);
}

void manage_pipes(t_exec_data *current, int *previous_pipe)
{
    if (current->pipe[1] >= 0)
        close(current->pipe[1]);
    if (previous_pipe[0] >= 0)
        close(previous_pipe[0]);
    previous_pipe[0] = current->pipe[0];
    previous_pipe[1] = current->pipe[1];
}



