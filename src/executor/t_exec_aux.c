#include "../../inc/minishell.h"


void close_pipe(int *pipe_fd)
{
    if (pipe_fd[0] >= 0) 
        close(pipe_fd[0]);
    if (pipe_fd[1] >= 0) 
        close(pipe_fd[1]); 
}

void t_extended_exec_data_init(t_extended_exec_data *exec_data)
{
    exec_data->cmd = NULL;
    exec_data->opt = NULL;
    exec_data->env = NULL;
    exec_data->is_builtin = false;
    exec_data->append_output = false;
    exec_data->exit_status = 0;
    exec_data->infile = NULL;
    exec_data->outfile = NULL;
    exec_data->here_doc_terminator = NULL;
}

void t_extended_exec_data_free(t_extended_exec_data *commands)
{
    t_extended_exec_data *temp;
    while (commands)
    {
        temp = commands;
        commands = commands->next;
        if (temp->cmd)
            free(temp->cmd);
        if (temp->opt)
            free(temp->opt);
        if (temp->env)
            free(temp->env);
        if (temp->infile)
            free(temp->infile);
        if (temp->outfile)
            free(temp->outfile);
        if (temp->here_doc_terminator)
            free(temp->here_doc_terminator);
        close_pipe(temp->pipe);
        free(temp);
    }
}


