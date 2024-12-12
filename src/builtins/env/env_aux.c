#include "../../../inc/minishell.h"

void env_print(t_env *head)
{
    if (!head)
        return ;

    while (head)
    {
        if (head->name)
        {
            if (head->name && head->value && head->visible)
                printf("%s=%s\n", head->name, head->value);
        }
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

void env_free(t_env *head)
{
    t_env *tmp;

    if (!head)
        return ;
    tmp = head;
    while(head)
    {
        tmp = head;
        head = head->next;
        if (tmp->name)
            free(tmp->name);
        if (tmp->value)
            free(tmp->value);
        free(tmp);
    }
}