#include "../../../inc/minishell.h"

size_t	env_len(t_env *env)
{
	size_t	count;
	t_env	*head;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**env_to_array(t_env *env)
{
	char	**list;
    char    *temp;
    int     i;

    list = safe_malloc(sizeof (char*) * (env_len(env) + 1), "env_to_array @ env_aux.c");
	i = 0;
    while (env)
    {
        temp = ft_strjoin(env->name, "=");
        if (!temp)
        {
            free_array(list, temp);
            error_exit("Malloc error!", "env_to_array @ env_aux.c");
        }
        list[i] = ft_strjoin(temp, env->value);
        if (!list[i] || !temp)
        {
            free_array(list, temp);
            error_exit("Malloc error!", "env_to_array @ env_aux.c");
        }
        free(temp);
        env = env->next;
        i++;
    }
	return (list);
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