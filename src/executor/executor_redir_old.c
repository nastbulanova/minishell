#include "../../inc/minishell.h"


static void handle_input_redirection(t_redir *current, int *temp_input_fd, char **error_message)
{
    errno = 0;
    close_fd(temp_input_fd);

    *temp_input_fd = open(current->str, O_RDONLY);
    if (*temp_input_fd < 0)
    {
        current->error = ft_strdup(strerror(errno));
        *error_message = current->error;
    }
}
static void handle_output_redirection(t_redir *current, int *temp_output_fd, char **error_message)
{
    errno = 0;
    close_fd(temp_output_fd);
    if (access(current->str, F_OK) == 0) 
    {
        if (access(current->str, W_OK) != 0) 
        {
            current->error = ft_strdup("Permission denied");
            *error_message = current->error;
            return;
        }
    }
    if (current->type == OUTPUT_APPEND)
        *temp_output_fd = open(current->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (current->type == OUTPUT)
        *temp_output_fd = open(current->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (*temp_output_fd < 0)
    {
        current->error = ft_strdup(strerror(errno));
        *error_message = current->error;
    }
    //fprintf(stderr, "File: %s FD: %d\n", current->str, *temp_output_fd);
}
static void finalize_redirections(t_exec_data *head, int *temp_input_fd, int *temp_output_fd, char *error_message)
{
    if (error_message)
    {
        //fprintf(stderr, "This CMD:%s has an error.\n", head->cmd);
        close_fd(temp_input_fd);
        close_fd(temp_output_fd);
    }
    else
    {
        //fprintf(stderr, "This CMD:%s has NO error.TempInput %d TempOutput %d\n", head->cmd, *temp_input_fd, *temp_output_fd);
        close_fd(&head->input_fd);
        if (*temp_input_fd >= 0)
            head->input_fd = *temp_input_fd;
        close_fd(&head->output_fd);
        if (*temp_output_fd >= 0)
            head->output_fd = *temp_output_fd;
        //fprintf(stderr, "This CMD:%s has NO error.Input %d Output %d\n", head->cmd, head->input_fd, head->output_fd);
    }
}
void handle_other_redirections(t_exec_data *head)
{
    t_redir *current;
    char *error_message;
    int temp_input_fd;
    int temp_output_fd;

    error_message = NULL;
    temp_input_fd = -1;
    temp_output_fd = -1;
    current = head->redirs; 
    while (current && !error_message)
    {
        //fprintf(stderr, "CMD:%s Start Redirection\n", head->cmd);
        if (current->type != HEREDOC && current->type != HEREDOC_QUOTED)
        {
            errno = 0;
            if (current->type == INPUT)
                handle_input_redirection(current, &temp_input_fd, &error_message);
            else
                handle_output_redirection(current, &temp_output_fd, &error_message);
        }
        current = current->next;
    }
    finalize_redirections(head, &temp_input_fd, &temp_output_fd, error_message);
}



