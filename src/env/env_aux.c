#include "../inc/minishell.h"

void env_print(t_env *head)
{
    if (!head)
        return ;

    while (head)
    {
        if (!head->name)
            ft_printf("Print NULL head found\n");
        if (head->name && head->value && head->visible)
            printf("%s=%s\n", head->name, head->value);
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

int array_len(char **split)
{
    int i;

    i = 0;
    while (split[i])
        i++;

    return (i);
}
