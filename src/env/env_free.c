#include "../inc/env.h"

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
