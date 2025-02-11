/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:23:37 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/11 18:07:12 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Removes environment variables from the shell's environment.
 * 
 * This function deletes environment variables specified in the `args` array
 * from the shell's environment list. It retrieves the current shell instance,
 * determines the starting index for arguments, and iterates over the provided 
 * variable names. If a matching environment variable is found, it is removed.
 * 
 * @param args A NULL-terminated array of strings containing variable 
 * names to unset.
 * @return Always returns 0.
 * 
 * @note This function modifies the global environment list stored in 
 * `t_minishell`.
 *       If a variable does not exist, it is simply skipped.
 */
int	cmd_unset(char **args)
{
	int			first_arg;
	t_env		*to_delete;
	t_minishell	*data;

	data = get_shell(false);
	first_arg = index_arg(args, get_cmd_flags(args[0]));
	while (first_arg >= 0 && args[first_arg])
	{
		to_delete = env_retrieve(data->env, args[first_arg]);
		if (to_delete)
		{
			env_delete(&data->env, to_delete->name);
			to_delete = NULL;
		}
		first_arg++;
	}
	return (0);
}
