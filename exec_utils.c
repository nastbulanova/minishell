#include "minishell.h"

int	env_len(t_env *env)
{
	int		count;
	t_env	*head;

	head = env;
	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**env_list_to_array(t_env *env)
{
	char	**list;
	t_env	*head;
	int		i;
	int		count;

	count = env_len(env);
	list = (char **)malloc(sizeof(char *) * (count + 1));
	//if (!list)
	//
	head = env;
	i = 0;
	while (i < count)
	{
		list[i] = ft_strjoin(ft_strjoin(head->name, "="), head->value);
		//if (!list[i])
		// free(whole list)
		head = head->next;
		i++;
	}
	list[i] = NULL;
	return (list);
}
