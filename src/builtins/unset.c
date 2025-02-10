/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:23:37 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:23:39 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
