/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:47:08 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:55:42 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	free_name_value(char *name, char *value)
{
	if (name)
		free(name);
	if (value)
		free(value);
}

static bool	process_arg(char *arg, t_minishell *data)
{
	char	*var_name;
	char	*var_value;
	char	*p;
	bool	result;

	result = false;
	p = ft_strchr(arg, '=');
	if ((p && p != arg) || (!p && is_valid_variable_name(arg)))
	{
		result = true;
		if (p)
			extract_name_value(arg, &var_name, &var_value);
		else
		{
			var_name = ft_strdup(arg);
			var_value = NULL;
		}
		result = is_valid_variable_name(var_name);
		if (result && var_value)
			update_env(data, var_name, var_value);
		else
			free_name_value(var_name, var_value);
	}
	return (result);
}

static void	set_process_exit(t_minishell *data, int count_error)
{
	if (count_error == 0)
		data->exit_code = 0;
	else
		data->exit_code = 1;
}

int	cmd_export(char **args)
{
	int			arg_count;
	int			first_arg;
	int			count_error;
	t_minishell	*data;

	data = get_shell(false);
	count_error = 0;
	arg_count = array_size(args) - 1;
	if (arg_count == 0)
		exp_print(data);
	else if (arg_count > 0)
	{
		first_arg = index_arg(args, get_cmd_flags(args[0]));
		while (first_arg >= 0 && args[first_arg])
		{
			if (!process_arg(args[first_arg], data) && !count_error)
			{
				count_error++;
				print_error_export(args[first_arg]);
			}
			first_arg++;
		}
	}
	set_process_exit(data, count_error);
	return (data->exit_code);
}
