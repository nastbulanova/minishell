/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:21:20 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/20 15:56:42 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

size_t	env_len(t_env *env)
{
	size_t	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char	**env_to_array(t_env *env)
{
	char	**list;
	char	*temp;
	int		i;

	list = safe_malloc(sizeof(char *) * (env_len(env) + 1));
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->name, "=");
		if (temp && env->value)
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

void	env_print(t_env *head)
{
	if (!head)
		return ;
	while (head)
	{
		
		if (head->name && head->value)
		{
			if (head->value[0] != '\0')
				printf("%s=%s\n", head->name, head->value);
		}
		head = head->next;
	}
}

void	env_add(t_env **head, t_env *new)
{
	t_env	*tmp;

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
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	env_free(t_env *head)
{
	t_env	*tmp;

	if (!head)
		return ;
	tmp = head;
	while (head)
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
