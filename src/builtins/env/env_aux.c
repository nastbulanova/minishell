/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:21:20 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/26 15:55:20 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Calculates the number of environment variables in the linked list.
 *
 * @param env Pointer to the head of the environment variable linked list.
 * @return The number of environment variables in the list.
 */
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

/**
 * @brief Converts the environment variable linked list into an array of strings.
 *
 * Each string in the resulting array follows the format "NAME=VALUE".
 *
 * @param env Pointer to the head of the environment variable linked list.
 * @return A dynamically allocated NULL-terminated array of environment strings.
 *         The caller is responsible for freeing this array.
 */
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
		else if (temp)
			list[i] = ft_strdup(temp);
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

/**
 * @brief Prints the environment variables to standard output.
 *
 * Only prints variables that have a non-empty name and a non-empty value.
 *
 * @param head Pointer to the head of the environment variable linked list.
 */
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

/**
 * @brief Adds a new environment variable to the end of the linked list.
 *
 * @param head Pointer to the pointer of the head of the linked list.
 * @param new Pointer to the new environment variable node to add.
 */
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

/**
 * @brief Frees all memory associated with the environment variable linked list.
 *
 * This function iterates through the list, freeing each node and its associated
 * name and value strings.
 *
 * @param head Pointer to the head of the environment variable linked list.
 */
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
