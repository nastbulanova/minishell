#include "../../inc/minishell.h"

char *built_error_string(char* filename, char *error_str)
{
    size_t filename_size = 0;
    size_t error_str_size = 0;
    size_t final_length = 0;
    char *final_string;
    char *template = "minishell: ";
    size_t index = 0;
    size_t temp_index = 0;


    filename_size = c_strlen(filename);
    error_str_size = c_strlen(error_str);
    final_length = (c_strlen(template) + filename_size + 2 + error_str_size + 1);
    final_string = safe_malloc(final_length);
    while (index < c_strlen(template))
    {
        final_string[index] = template[index];
        index++;
    }
    //fprintf(stderr, "%s\n", final_string);
    while (temp_index < filename_size)
    {
        final_string[index] = filename[temp_index];
        temp_index++;
        index++;
    }
    final_string[index++] = ':';
    final_string[index++] = ' ';
    //fprintf(stderr, "%s\n", final_string);
    temp_index = 0;
    while (temp_index < error_str_size)
    {
        final_string[index] = error_str[temp_index];
        temp_index++;
        index++;
    }
    //final_string[index++] = '\n';
    final_string[index] = '\0';
    return final_string;
}


void setup_child_redirections(t_exec_data *current, t_exec_data *previous)
{
     fprintf(stderr, "  Child CMD %s: outfile_fd %d \n", current->cmd, current->output_fd);
    if (current->output_fd >= 0)
    {
        fprintf(stderr, "Child CMD %s: STDOUT to outfile_fd %d \n", current->cmd, current->output_fd);
        //dup2(current->output_fd, STDOUT_FILENO);
        safe_dup_two(current->output_fd, STDOUT_FILENO);
        close_fd(&current->output_fd);
    }
    else if (current->next) 
    {
        fprintf(stderr, "Child CMD %s: STDOUT to outpipe[1] %d \n", current->cmd, current->outpipe[1]);
        //dup2(current->outpipe[1], STDOUT_FILENO);
        safe_dup_two(current->outpipe[1], STDOUT_FILENO);
    }
    //fprintf(stderr, "Child CMD %s: Closing to outpipe[0] %d \n", current->cmd, current->outpipe[0]);
    //fprintf(stderr, "Child CMD %s: Closing to outpipe[1] %d \n", current->cmd, current->outpipe[1]);
    close_fd(&current->outpipe[0]); // Close read end
    close_fd(&current->outpipe[1]); // Close write end if redirected
    if (current->input_fd >= 0) 
    {
        fprintf(stderr, "Child CMD %s: STDIN to input_fd %d \n", current->cmd, current->input_fd);
        //dup2(current->input_fd, STDIN_FILENO);
        
        safe_dup_two(current->input_fd, STDIN_FILENO);
        fprintf(stderr, "Child CMD %s: Closing input_fd %d \n", current->cmd, current->input_fd);
        close(current->input_fd);
    } 
    else if (previous && previous->outpipe[0] >= 0) 
    {
        //fprintf(stderr, "Child CMD %s: STDIN to previous->outpipe[0] %d \n", current->cmd, previous->outpipe[0]);
        //dup2(previous->outpipe[0], STDIN_FILENO);
        safe_dup_two(previous->outpipe[0], STDIN_FILENO);
    }
    if (previous) 
    {
        //fprintf(stderr, "Child CMD %s: Closing previous outpipe[0] %d && outpipe[1] %d\n", current->cmd, previous->outpipe[0], previous->outpipe[1]);
        close_fd(&previous->outpipe[0]);
        close_fd(&previous->outpipe[1]);
        close_fd(&previous->output_fd);
        close_fd(&previous->input_fd);
    }
    
}

static void handle_builtin_in_child(t_exec_data *current)
{
    //int exit_status;
    check_redir(current);
    if (c_strcmp(current->cmd, "echo") == 0)
    {
        close_fd(&current->input_fd);
        close(STDIN_FILENO);
        current->exit_status = cmd_echo(current->opt);
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
    {
        current->exit_status = cmd_pwd(current->output_fd);
    }
    else
        minishell_exit("Critical error processing built in.", 2, STDERR_FILENO, false);
    exit(current->exit_status);
}

void check_redir(t_exec_data *current)
{
    t_redir *head;
    head = current->redirs;
    while (head)
    {
    //fprintf(stderr, "HIT %s\n", head->error);
        if (head->error)
            break;
        head = head->next;
    }
    if (head && head->error && head->str)
    {
        //fprintf(stderr, "check_redir str: %s error: %s\n", head->str, head->error);
        minishell_exit(built_error_string(head->str, head->error),1, STDERR_FILENO, false);
    }
}
void handle_child(t_exec_data *current, t_exec_data *previous, char **envp)
{
   
    setup_child_redirections(current, previous);
    if (current->is_builtin)
    {
        handle_builtin_in_child(current);
    }
    else
    {   
        errno = 0;
        check_redir(current);
        if (!current->cmd || access(current->cmd, F_OK) != 0)
        {
            minishell_exit(built_error_string(current->cmd, strerror(errno)), 127, STDERR_FILENO, false);
            return;
        }
        if(execve(current->cmd, current->opt, envp) == -1)
            minishell_exit(built_error_string(current->cmd, strerror(errno)), 127, STDERR_FILENO, true);
    }
}

