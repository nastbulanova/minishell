#include "../../inc/minishell.h"


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

void handle_exit_status(t_pid_list *pid_list)
{
    t_minishell *data;
    int status;
    int signal;

    data = get_shell(false);
    while(pid_list)
    {
        //fprintf(stderr, "Waiting on : PID: %d\n", pid_list->pid);
        waitpid(pid_list->pid, &status, 0);
        if (WIFEXITED(status)) 
            data->exit_code = WEXITSTATUS(status); 
        else if (WIFSIGNALED(status)) 
        {
            signal = WTERMSIG(status);
            data->exit_code = 128 + signal; 
        }
        else
            data->exit_code = 1;
        fprintf(stderr, "Left: PID: %d exit_code: %d\n", pid_list->pid, data->exit_code);
        pid_list = pid_list->next;
    }
}