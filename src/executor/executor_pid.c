#include "../../inc/minishell.h"

pid_t safe_fork()
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        minishell_exit("failed fork @ safe_fork (executor_pid)", 1, STDERR_FILENO); 
    return (pid);
}
pid_t get_last_pid(t_pid_list *head)
{
    if (!head) 
        return -1; 

    t_pid_list *current = head;
    while (current->next)
        current = current->next;

    return current->pid; 
}

t_pid_list *create_pid_node(pid_t pid)
{
    t_pid_list *new_node = safe_malloc(sizeof(t_pid_list));
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





