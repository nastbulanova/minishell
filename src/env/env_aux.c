#include "../inc/env.h"

void env_print(t_env *head)
{
    ft_printf("Printing env\n");
    if (!head)
        return ;

    while (head)
    {
        if (!head->name)
            ft_printf("Print NULL head found\n");
        if (head->name && head->value)
            printf("Print: %s=%s\n", head->name, head->value);
        head = head->next;
    }
}

void env_add(t_env **head, t_env *new)
{
    t_env *tmp;

    if (!new || !head)
        return ;
    if (!*head)
    {
        *head = new;
        return ;
    }
    else
    {
        tmp = *head; 
        while(tmp->next)
            tmp = tmp->next;
        tmp->next = new;   
    }
}

void env_remove(t_env **head, char *name)
{
    t_env *current;
    t_env *previous;
    int str_len;

    if (!head || !*head)
        return ;
    previous = NULL;
    current = *head; 
    str_len = ft_strlen(name);
    while(current)
    {
        if (!ft_strncmp(current->name, name, str_len))
        {
            if (previous)
                previous->next = current->next;
            else    
                *head = current->next;
            free(current->name);
            free(current->value);
            free(current);  
            return ;
        }
        previous = current;
        current = current->next;
    }
}

