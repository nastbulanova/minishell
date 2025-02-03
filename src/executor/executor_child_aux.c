#include "../../inc/minishell.h"

void free_pid_list(t_pid_list **head)
{
    t_pid_list *current = *head;
    t_pid_list *next;

    while (current)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

t_pid_list *create_pid_node(pid_t pid)
{
    t_pid_list *new_node;

    new_node = safe_malloc(sizeof(t_pid_list));
    new_node->pid = pid;
    new_node->next = NULL;
    return (new_node);
}

void add_pid(t_pid_list **head, pid_t pid)
{
    t_pid_list *new_node;
    t_pid_list *current;

    new_node = create_pid_node(pid);
    if (!new_node)
        return;
    if (!*head)
    {
        *head = new_node;
        return;
    }
    current = *head;
    while (current->next)
        current = current->next;
    current->next = new_node;  
}

void handle_exit_status(t_minishell *data, t_pid_list *pid_list)
{
    int status;
    int signal;
    t_pid_list *current;

    current = pid_list;
    while(current)
    {
        waitpid(current->pid, &status, 0);
        if (WIFEXITED(status)) 
            data->exit_code = WEXITSTATUS(status); 
        else if (WIFSIGNALED(status)) 
        {
            signal = WTERMSIG(status);
            data->exit_code = 128 + signal; 
        }
        else
            data->exit_code = 1;
        fprintf(stderr, "Left: PID: %d exit_code: %d\n", current->pid, data->exit_code);
        current = current->next;
    }
    free_pid_list(&pid_list);
}
