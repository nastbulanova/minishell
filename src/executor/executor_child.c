#include "../../inc/minishell.h"

char *built_error_string(const char* filename)
{
    size_t final_length;
    size_t filename_length;
    char template[] = "minishell: : No such file or directory\n";
    char *result;
    size_t template_index;
    size_t filename_index;
    if (filename)
        filename_length = ft_strlen(filename);
    else
        filename_length = 0;
    final_length = filename_length + sizeof(template);
    result = safe_malloc(final_length);
    template_index = -1;
    filename_index = -1;
    while (++template_index < 11)
        result[template_index] = template[template_index];
    while (++filename_index < filename_length)
        result[template_index + filename_index] = filename[filename_index];
    while (template_index + filename_index < final_length)
    {
        result[template_index + filename_index] = template[template_index];
        template_index++;
    }
    return (result);
}


void setup_child_redirections(t_exec_data *current, t_exec_data *previous)
{
    if (current->output_fd >= 0)
    {
        //fprintf(stderr, "Child CMD %s: STDOUT to outfile_fd %d \n", current->cmd, current->output_fd);
        //dup2(current->output_fd, STDOUT_FILENO);
        safe_dup_two(current->output_fd, STDOUT_FILENO);
        close_fd(&current->output_fd);
    }
    else if (current->next) 
    {
        //fprintf(stderr, "Child CMD %s: STDOUT to outpipe[1] %d \n", current->cmd, current->outpipe[1]);
        //dup2(current->outpipe[1], STDOUT_FILENO);
        safe_dup_two(current->outpipe[1], STDOUT_FILENO);
    }
    //fprintf(stderr, "Child CMD %s: Closing to outpipe[0] %d \n", current->cmd, current->outpipe[0]);
    //fprintf(stderr, "Child CMD %s: Closing to outpipe[1] %d \n", current->cmd, current->outpipe[1]);
    close_fd(&current->outpipe[0]); // Close read end
    close_fd(&current->outpipe[1]); // Close write end if redirected
    if (current->input_fd >= 0) 
    {
        //fprintf(stderr, "Child CMD %s: STDIN to input_fd %d \n", current->cmd, current->input_fd);
        //dup2(current->input_fd, STDIN_FILENO);
        safe_dup_two(current->input_fd, STDIN_FILENO);
        //fprintf(stderr, "Child CMD %s: Closing input_fd %d \n", current->cmd, current->input_fd);
        close_fd(&current->input_fd);
    } 
    else if (previous) 
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
    }
    
}

static void handle_builtin_in_child(t_exec_data *current)
{
    int exit_status;

    if (c_strcmp(current->cmd, "echo") == 0)
        exit_status = cmd_echo(current->opt);
    else if (c_strcmp(current->cmd, "cd") == 0)
        exit_status = cmd_cd(current->opt);
    else if (c_strcmp(current->cmd, "unset") == 0)
        exit_status = cmd_unset(current->opt);
    else if (c_strcmp(current->cmd, "export") == 0)
        exit_status = cmd_export(current->opt);
    else if (c_strcmp(current->cmd, "exit") == 0)
        exit_status = cmd_exit(current->opt);
    else if (c_strcmp(current->cmd, "env") == 0)
        exit_status = cmd_env(current->opt);
    else if (c_strcmp(current->cmd, "pwd") == 0)
        exit_status = cmd_pwd(current->opt);
    else
        minishell_exit("Critical error processing built in.", 2, STDERR_FILENO, false);
    exit(exit_status);
}

void check_redir(t_exec_data *current)
{
    t_redir *head;

    head = current->redirs;
    while (head)
    {
        if (head->str)
            break;
        head = head->next;
    }
    minishell_exit(built_error_string(head->str),1, STDERR_FILENO, true);
}
void handle_child(t_exec_data *current, t_exec_data *previous, char **envp)
{
   
    //fprintf(stderr, "CMD %s Input:%d Output:%d pipe[%d][%d]\n", current->cmd, current->input_fd, current->output_fd, current->outpipe[0], current->outpipe[1]);
    setup_child_redirections(current, previous);
    if (current->is_builtin)
        handle_builtin_in_child(current);
    else
    {
        if (!current->cmd || access(current->cmd, F_OK) != 0)
            minishell_exit(built_error_string(current->cmd),1, STDERR_FILENO, true);
        if(execve(current->cmd, current->opt, envp) == -1)
        {
            perror("execve failed");
            perror(strerror(errno));
            exit(EXIT_FAILURE);
        }
    }
}

