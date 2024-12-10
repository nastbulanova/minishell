#include "../inc/minishell.h"

void env_update(t_env *target, const char *new_value)
{
    if (!new_value)
        return ;
    if (target->value)
        free(target->value);
    if (new_value)
        target->value = ft_strdup(new_value);
    else
        target->value = NULL;
    target->visible = true;
    if (!target->value && new_value)
        error_exit(RB "" RST, "env_update in env_crud.c");
}
void env_delete(t_env **head, char *name)
{
    t_env *current;
    t_env *previous;

    if (!head || !*head)
        return ;
    previous = NULL;
    current = *head; 
    while(current)
    {
        if (!c_strcmp(current->name, name))
        {
            if (!c_strcmp(current->name, "OLDPWD"))
                current->visible = false;
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

t_env *env_create(char *name, char *value)
{
    t_env *new;

    new = safe_malloc(sizeof(t_env), "env_new in env_aux.c");
    new->name = ft_strdup(name);
    if (value)
        new->value = ft_strdup(value);
    else
        new->value = NULL;
    new->visible = true;
    new->next = NULL;
    return (new);
}

t_env *env_retrieve(t_env *head, char *name)
{
    if (!name || !*name)
        return (NULL);
    
    while (head)
    {   
        if (!c_strcmp(head->name, name))
            return (head);
        head = head->next;
    }
    return (NULL);
}