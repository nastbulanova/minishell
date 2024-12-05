#include "../inc/minishell.h"

void exp_init(t_minishell *shell)
{
    t_env *new;
    t_env **head;
    t_env *env_head;

    head = &shell->exp;
    env_head = shell->env;
    while(env_head)
    {
        new = env_create(env_head->name, env_head->value);
        if (new)
            env_add(head, new);
        env_head = env_head->next;
    }
}




