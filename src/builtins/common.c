/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:24:26 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:42:28 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_mul_flg(char *arg, char **flags)
{
	int		i;
	char	*p;

	if (arg[0] == '-')
	{
		i = 0;
		while (flags[i])
		{
			p = ft_strchr(arg, flags[i][0]);
			if (!p)
				return (false);
			i++;
		}
	}
	else
		return (false);
	return (true);
}

int	index_arg(char **args, char **flags)
{
	int	i;
	int	j;
	int	is_flag;

	if (!args || !args[0])
		return (-1);
	i = 0;
	while (args[++i])
	{
		is_flag = 0;
		if (args[i][0] == '-')
			is_flag = 1;
		j = -1;
		while (flags && flags[++j] && !is_flag)
		{
			if (c_strcmp(args[i], flags[j]) == 0 || is_mul_flg(args[i], flags))
			{
				is_flag = 1;
				break ;
			}
		}
		if (!is_flag)
			return (i);
	}
	return (-1);
}

int	array_size(char **array)
{
	int	result;

	result = 0;
	if (!array)
		return (result);
	while (array[result])
		result++;
	return (result);
}

bool	has_flag(char **args, char *flag)
{
	int		first_arg;
	int		i;
	char	**flags;

	if (!args || !args[0])
		return (false);
	if (!flag)
		return (false);
	flags = get_cmd_flags(args[0]);
	if (!flags)
		return (false);
	first_arg = index_arg(args, get_cmd_flags(args[0]));
	if (first_arg < 0)
		first_arg = array_size(args);
	i = -1;
	while (++i < first_arg)
	{
		if (!c_strcmp(flag, args[i]) || ft_strchr(args[i], flag[1]))
			return (true);
	}
	return (false);
}

char	**get_cmd_flags(char *command)
{
	if (!command)
		return (NULL);
	if (!c_strcmp(command, "echo"))
		return (get_flags_echo());
	else if (!c_strcmp(command, "cd"))
		return (get_flags_cd());
	else if (!c_strcmp(command, "pwd"))
		return (get_flags_null());
	else if (!c_strcmp(command, "export"))
		return (get_flags_export());
	else if (!c_strcmp(command, "unset"))
		return (get_flags_unset());
	else if (!c_strcmp(command, "env"))
		return (get_flags_null());
	else if (!c_strcmp(command, "exit"))
		return (get_flags_null());
	return (NULL);
}
