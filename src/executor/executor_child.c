#include "../../inc/minishell.h"

void clear_fds(t_exec_data *temp)
{
    while (temp) 
    {
        if (temp->input_fd >= 0)
            close_fd(&temp->input_fd);
        if (temp->output_fd >= 0) 
            close_fd(&temp->output_fd);
        if (temp->outpipe[0] >= 0)
            close_fd(&temp->outpipe[0]);
        if (temp->outpipe[1] >= 0)
            close_fd(&temp->outpipe[1]);
        temp = temp->next;
    }
}

void handle_parent(t_exec_data *cmd, t_exec_data *previous, t_pid_list **pid_list, pid_t pid)
{
    add_pid(pid_list, pid);
    if (cmd->outpipe[1] >= 0) 
        close_fd(&cmd->outpipe[1]);
    if (previous && previous->outpipe[0] >= 0) 
        close_fd(&previous->outpipe[0]);
    if (cmd->input_fd >= 0) 
        close_fd(&cmd->input_fd);
    if (cmd->output_fd >= 0) 
        close_fd(&cmd->output_fd);
}

static void handle_child_input(t_exec_data *cmd, t_exec_data *previous)
{
    if (cmd->input_fd >= 0) 
    {
        if (!cmd->is_builtin)
            safe_dup_two(cmd->input_fd, STDIN_FILENO);
        close_fd(&cmd->input_fd);
    }
    else if (previous) 
    {   
        if (previous->outpipe[0] >= 0)
        {
            //fprintf(stderr, "Previous CMD %s has outpipe[%d]", previous->cmd, previous->outpipe[0]);
            safe_dup_two(previous->outpipe[0], STDIN_FILENO); 
            close_fd(&previous->outpipe[0]);
        }
    }
}

static void handle_child_output(t_exec_data *cmd)
{
    if (cmd->output_fd >= 0) 
    {
        safe_dup_two(cmd->output_fd, STDOUT_FILENO);
        close_fd(&cmd->output_fd);
    } 
    else if (cmd->next) 
    {
        if (cmd->outpipe[1] >= 0)
        {
            safe_dup_two(cmd->outpipe[1], STDOUT_FILENO);
            close_fd(&cmd->outpipe[1]);
        }
    }
}

void handle_child(t_exec_data *cmd, t_exec_data *previous, char **envp, t_exec_data *head)
{
    int exit_code;
    t_minishell *data;

    data = get_shell(false);
    exit_code = 0;
    handle_child_input(cmd, previous);
    handle_child_output(cmd);
    if (cmd->next) 
        close_fd(&cmd->outpipe[0]);
    if (previous) 
        close_fd(&previous->outpipe[1]);
    //fprintf(stderr, "   CMD %s After child redirect input_fd %d, output_fd %d, outpit[%d][%d]\n", cmd->cmd, cmd->input_fd, cmd->output_fd, cmd->outpipe[0], cmd->outpipe[1]);
    //clear_fds(cmd->next);
    if (cmd->is_builtin)
    {
        if (command_is_valid(cmd, data))
        {
            exit_code = execute_builtin(cmd);
        }
        clear_fds(head);
        //fprintf(stderr, "   CMD %s After execute_builtin input_fd %d, output_fd %d, outpit[%d][%d]\n", cmd->cmd, cmd->input_fd, cmd->output_fd, cmd->outpipe[0], cmd->outpipe[1]);
        minishell_exit(NULL, exit_code, STDOUT_FILENO, false);
    }
    else
    {
        //fprintf(stderr, "   CMD %s before  execute_execve input_fd %d, output_fd %d, outpit[%d][%d]\n", cmd->cmd, cmd->input_fd, cmd->output_fd, cmd->outpipe[0], cmd->outpipe[1]);
        if (command_is_valid(cmd, data))
        {
            execute_execve(cmd, envp, head);    
        }
        else
        {
            clear_fds(head);
            minishell_exit(NULL, data->exit_code, STDERR_FILENO, true);
        }
    }
}




