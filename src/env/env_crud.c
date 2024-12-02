#include "../inc/minishell.h"

void env_update(t_env *target, const char *new_value)
{
    if (!new_value)
        return ;
    if (target->value)
        free(target->value);
    target->value = ft_strdup(new_value);
    if (!target->value)
        error_exit(RB "" RST, "env_update in env_crud.c");
}
void env_delete(t_env **head, char *name)
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
            if (!ft_strncmp(current->name, "OLDPWD", 7))
            {
                current->visible = false;
            }
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
    new->value = ft_strdup(value);
    new->visible = true;
    new->next = NULL;
    return (new);
}

t_env *env_retrieve(t_env *head, char *name)
{
    int name_len;
    if (!name || !*name)
        return (NULL);
    
    while (head)
    {   name_len = ft_strlen(name);
        if (!ft_strncmp(head->name, name, name_len))
            return (head);
        head = head->next;
    }
    return (NULL);
}