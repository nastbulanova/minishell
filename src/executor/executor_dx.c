#include "../../inc/minishell.h"

void handle_parent(t_exec_data *current, t_exec_data *previous, t_pid_list **pid_list, pid_t pid)
{
        add_pid(pid_list, pid);
        if (current->input_fd >= 0) 
        {
            fprintf(stderr, "Parent: Closing input_fd %d for CMD %s\n", current->input_fd, current->cmd);
            //close_fd(&current->input_fd);
            close(current->input_fd);
            if (previous) 
            {
                //fprintf(stderr, "Parent: Closing previous->outpipe[0] %d\n", previous->outpipe[0]);
                close_fd(&previous->outpipe[0]);
            }
        }
        if (current->output_fd >= 0) 
        {
            fprintf(stderr, "Parent: Closing output_fd %d for CMD %s\n", current->output_fd, current->cmd);
            close_fd(&current->output_fd);
        }
        if (previous) 
        {
            //fprintf(stderr, "Parent: Closing previous->outpipe[0] %d\n", previous->outpipe[0]);
            close_fd(&previous->outpipe[0]);
            //fprintf(stderr, "Parent: Closing previous->outpipe[1] %d\n", previous->outpipe[1]);
            close_fd(&previous->outpipe[1]);
            close_fd(&previous->output_fd);
            close_fd(&previous->input_fd);
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
    current = head;
    
         while (current)
         {
            if (current->input_fd >= 0)
                close(current->input_fd);
            if (current->output_fd >= 0)
                close(current->output_fd);
         current = current->next;
         }
    
    free_pid_list(&pid_list);
}
bool check_redir_parent(t_exec_data *current)
{
    t_redir *head;
    char    *temp;
    t_minishell *data;

    head = current->redirs;
    while (head)
    {
    //fprintf(stderr, "HIT %s\n", head->error);
        if (head->error)
            break;
        head = head->next;
    }
    if (head && head->error)
    {
        data = get_shell(false);
        temp = built_error_string(head->str, head->error);
        write(STDERR_FILENO, temp, ft_strlen(temp));
        free(temp);
        data->exit_code = 1;
        return (false);
    }
    return (true);
}
static void handle_builtin_command(t_exec_data *current)
{
    if (!check_redir_parent(current))
        return;
    if (c_strcmp(current->cmd, "echo") == 0)
    {
        close(STDIN_FILENO);
        current->exit_status = cmd_echo(current->opt, current->output_fd);
        
    }
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
        current->exit_status = cmd_pwd(current->output_fd);
    else
        minishell_exit("Critical error processing built in.", 2, STDERR_FILENO, false);
}

static void handle_command_redirections(t_minishell *data, t_exec_data *head)
{
    while (head)
    {
        handle_heredoc_redirection (head);
        if (data->exit_code == 130)
            return;
        handle_other_redirections(head);
        head = head->next;
    }
}

void execute_command_list_old(t_minishell *data, t_exec_data *head, char **envp)
{
   
    handle_command_redirections(data, head);
    if (data->exit_code == 130)
        return;
    if (!head->next && head->is_builtin)
        handle_builtin_command(head);
    else
        handle_pipe_sequence(head, envp);
}

