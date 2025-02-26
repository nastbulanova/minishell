/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:29:46 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/26 15:37:48 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Updates the last executed command in the environment variable '_'.
 * 
 * @param env_head Pointer to the head of the environment variable list.
 * @param command The command to store as the last executed command.
 * @return true if successful, false otherwise.
 */
bool	update_last_command(t_env *env_head, char *command)
{
	t_env	*node;
	char	*temp;

	node = env_retrieve(env_head, "_");
	if (!node)
	{
		node = env_create("_", command);
		if (!node)
			return (false);
	}
	else
	{
		temp = ft_strdup(command);
		if (!temp)
			return (false);
		if (node->value)
			free(node->value);
		node->value = temp;
	}
	return (true);
}

/**
 * @brief Prints the current environment variables.
 * 
 * @param argv Unused parameter.
 * @return 0.
 */
int	cmd_env(char **argv)
{
	t_minishell	*data;

	(void)argv;
	data = get_shell(false);
	env_print(data->env);
	return (0);
}
