/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:24:12 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:24:14 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_char_in_flag(char c, char **flags)
{
	int	i;

	i = 0;
	while (flags[i])
	{
		if (c == flags[i][0])
			return (true);
		i++;
	}
	return (false);
}

bool	is_string_flag(char *str, char **flags)
{
	int	i;

	if (ft_strlen(str) < 2 || str[0] != '-')
		return (false);
	i = 1;
	while (str && str[i])
	{
		if (!is_char_in_flag(str[i], flags))
			return (false);
		i++;
	}
	return (true);
}

static bool	flag_exists(char c, char **flags, char **args)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (args[i])
	{
		if (is_string_flag(args[i], flags))
		{
			while (args[i][j])
			{
				if (c == args[i][j])
					return (true);
				j++;
			}
		}
		i++;
	}
	return (false);
}

int	cmd_echo(char **args)
{
	bool	newline;
	int		first_arg;
	char	**command_args;

	command_args = get_cmd_flags(args[0]);
	newline = flag_exists('n', command_args, args);
	first_arg = 1;
	while (is_string_flag(args[first_arg], command_args))
		first_arg++;
	while (first_arg >= 0 && args[first_arg])
	{
		ft_putstr_fd(args[first_arg], STDOUT_FILENO);
		if (args[first_arg + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		first_arg++;
	}
	if (!newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
