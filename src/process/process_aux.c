#include "../../inc/minishell.h"

void print_process_list() 
{
    t_process *current = global_shell.process_head;
    if (!current) 
    {
        printf("No processes in the list.\n");
        return;
    }

    printf("Current process list:\n");
    while (current) 
    {
        printf("PID: %d\n", current->pid);
        current = current->next;
    }
}

void remove_process(pid_t pid) 
{
    t_process** current = &global_shell.process_head;
    while (*current) 
    {
        if ((*current)->pid == pid) 
        {
            t_process* to_delete = *current;
            *current = (*current)->next; 
            free(to_delete);             
            return;
        }
        current = &(*current)->next;
    }
}

void add_process(pid_t pid) 
{
    t_process* new_node = malloc(sizeof(t_process));
    if (new_node) 
    {
        new_node->pid = pid;
        new_node->next = global_shell.process_head;
        global_shell.process_head = new_node;
    }
}