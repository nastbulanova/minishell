#include "../inc/minishell.h"

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
