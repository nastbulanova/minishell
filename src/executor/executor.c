#include "../../inc/minishell.h"

static void execute_pipe(t_minishell *data, t_exec_data *head, char** envp)
{
    (void)data;
    (void)head;
    (void)envp;
    fprintf(stderr, "NOT IMPLEMENTED\n");
}

static void execute_isolated(t_minishell *data, t_exec_data *cmd, char **envp)
{
    int stdin_backup;   //consider storing these variables on initialization of our singleton to restore on application exit or whenever needed
    int stdout_backup;
    int stderr_backup;
    pid_t pid;

    if (cmd->exit_status != 0)//in the earlier setup stage a command could have its exit code preemptivly assigne (ir permission error on input / output)
    {
        data->exit_code = cmd->exit_status;
        close_fd(&cmd->input_fd);
        close_fd(&cmd->output_fd);
        char *error = get_rdir_error(cmd->redirs);
        if (error)
            ft_printf("%s\n", error);
        else
            fprintf(stderr, "No error found.\n");
        return;
    }

    stdin_backup = dup(STDIN_FILENO);
    stdout_backup = dup(STDOUT_FILENO);
    stderr_backup = dup(STDERR_FILENO);

    if (cmd->input_fd >= 0)
    {
        safe_dup_two(cmd->input_fd, STDIN_FILENO); 
        close(cmd->input_fd);
    }

    if (cmd->output_fd >= 0)
    {
        safe_dup_two(cmd->output_fd, STDOUT_FILENO); 
        close(cmd->output_fd);
    }
    if (cmd->is_builtin)
    {
        if (c_strcmp(cmd->cmd, "echo") == 0)
        {
            data->exit_code = cmd_echo(cmd->opt);
        }
        else if (c_strcmp(cmd->cmd, "cd") == 0)
            data->exit_code = cmd_cd(cmd->opt);
        else if (c_strcmp(cmd->cmd, "unset") == 0)
            data->exit_code = cmd_unset(cmd->opt);
        else if (c_strcmp(cmd->cmd, "export") == 0)
            data->exit_code = cmd_export(cmd->opt);
        else if (c_strcmp(cmd->cmd, "exit") == 0)
            data->exit_code = cmd_exit(cmd->opt);
        else if (c_strcmp(cmd->cmd, "env") == 0)
            data->exit_code = cmd_env(cmd->opt);
        else if (c_strcmp(cmd->cmd, "pwd") == 0)
        {
            data->exit_code = cmd_pwd(cmd->output_fd);
        }
        else
            minishell_exit("Critical error processing built in.", 2, STDERR_FILENO, false);
    }
    else
    {
        pid = safe_fork();
        if (pid == 0)
        {
            if (execve(cmd->cmd, cmd->opt, envp) < 0)
            {
                perror("execve");
                if (errno == ENOENT)
                    exit(127); // Command not found
                else if (errno == EACCES)
                    exit(126); // Permission denied
                else
                      exit(1); // General error
            }
        }
        else
        {
            int status;
            waitpid(pid, &status, 0); // Wait for the child to finish
            if (WIFEXITED(status)) 
            {
                data->exit_code = WEXITSTATUS(status); // Retrieve exit code
            }
        }
    }
    //if i decide to keep the original in my signleton should i dup2 or just dup here?
    dup2(stdin_backup, STDIN_FILENO);
    dup2(stdout_backup, STDOUT_FILENO);
    dup2(stderr_backup, STDERR_FILENO);
    close_fd(&stdin_backup);
    close_fd(&stdout_backup);
    close_fd(&stderr_backup); 
}


void handle_command_redirections(t_minishell *data, t_exec_data *head)
{
    while (head)
    {
        handle_heredoc_redirection (data, head);//tested no leaks
        if (data->exit_code == 130)//heredocs are process first in bash we can test this and ctrl+c stops execution of all commands
            break;
        handle_io_redirections(head);
        head = head->next;
    }
}

void execute_command_list(t_minishell *data, t_exec_data *head, char **envp)
{
    handle_command_redirections(data, head);
    if (data->exit_code == 130)
        return;
    if (!head->next)
        execute_isolated(data, head, envp);
    else
        execute_pipe(data, head, envp);

    while (head)
    {
        //close_fd(&head->input_fd);
        //close_fd(&head->output_fd);
        //close_pipe(head->outpipe);
        head = head->next;
    }
    
    
}

