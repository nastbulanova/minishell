#include "../../inc/minishell.h"

void handle_parent(t_exec_data *current, t_exec_data *previous, t_pid_list **pid_list, pid_t pid)
{
        add_pid(pid_list, pid);//this is just to wait till all processes complete later it's inocous in termos of fd handling
        // Parent process
        if (current->input_fd >= 0) 
        {
            // Close the input file if it exists
            fprintf(stderr, "Parent: Closing input_fd %d for CMD %s\n", current->input_fd, current->cmd);
            close_fd(&current->input_fd);
            // Also close the read end of the previous pipe if it exists
            if (previous) 
            {
                fprintf(stderr, "Parent: Closing previous->outpipe[0] %d\n", previous->outpipe[0]);
                close_fd(&previous->outpipe[0]);
            }
        }

        if (current->output_fd >= 0) 
        {
            // Close the output file if it exists
            fprintf(stderr, "Parent: Closing output_fd %d for CMD %s\n", current->output_fd, current->cmd);
            close_fd(&current->output_fd);
        }

        // If the previous command has a pipe, close its ends
        if (previous) 
        {
            fprintf(stderr, "Parent: Closing previous->outpipe[0] %d\n", previous->outpipe[0]);
            close_fd(&previous->outpipe[0]);
            fprintf(stderr, "Parent: Closing previous->outpipe[1] %d\n", previous->outpipe[1]);
            close_fd(&previous->outpipe[1]);
        }

}

static void handle_pipe_sequence(t_exec_data *head, char **envp)
{
    t_exec_data *current;
    t_exec_data *previous;
    t_pid_list *pid_list;
    pid_t       pid;

    current = head;
    pid_list = NULL;
    previous = NULL;
    while (current)
    {
        safe_pipe(current->outpipe);
        pid = safe_fork();
        if (pid == 0)
            handle_child(current, previous, envp); 
        else 
            handle_parent(current, previous, &pid_list, pid);
        previous = current;
        current = current->next;
    }
    handle_exit_status(pid_list);
    free_pid_list(&pid_list);
}

static void handle_builtin_command(t_exec_data *current)
{
    if (c_strcmp(current->cmd, "echo") == 0)
            current->exit_status = cmd_echo(current->opt);
    else if (c_strcmp(current->cmd, "cd") == 0)
        current->exit_status = cmd_cd(current->opt);
    else if (c_strcmp(current->cmd, "unset") == 0)
        current->exit_status = cmd_unset(current->opt);
    else if (c_strcmp(current->cmd, "export") == 0)
        current->exit_status = cmd_export(current->opt);
    else if (c_strcmp(current->cmd, "exit") == 0)
        current->exit_status = cmd_exit(current->opt);
    else if (c_strcmp(current->cmd, "env") == 0)
        current->exit_status = cmd_env(current->opt);
    else if (c_strcmp(current->cmd, "pwd") == 0)
        current->exit_status = cmd_pwd(current->opt);
    else
        minishell_exit("Critical error processing built in.", 2, STDERR_FILENO);
}

static void handle_command_redirections(t_exec_data *head)
{
    while (head)
    {
        handle_heredoc_redirection (head);
        handle_other_redirections(head);
        head = head->next;
    }
}

void execute_command_list(t_exec_data *head, char **envp)
{
    t_minishell *data;

    data = get_shell(false);
    handle_command_redirections(head);
    
    if (!head->next && head->is_builtin)
        handle_builtin_command(head);
    else
        handle_pipe_sequence(head, envp);
    while (head->next)
        head = head->next;
    data->exit_code = head->exit_status;
}

