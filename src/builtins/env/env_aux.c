#include "../../../inc/minishell.h"

void shlvl_init(t_env *head)
{
    t_env *lvl_shell;
    char *shell_lvl;
    int current_lvl;;

    lvl_shell = env_retrieve(head, "SHLVL");
    if (lvl_shell)
    {
        current_lvl = ft_atoi(lvl_shell->value);
        if (current_lvl < 0)
            current_lvl = 0;
        shell_lvl = ft_itoa(current_lvl + 1);
        env_update(lvl_shell, shell_lvl);
        free(shell_lvl);
    }
    else
        env_add(&head, env_create("SHLVL", "1"));
}

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
    if (!head || !*head)
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