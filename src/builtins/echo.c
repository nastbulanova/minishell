/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:24:12 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/11 18:06:55 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Checks if a character is present in the flag list.
 *
 * @param c The character to check.
 * @param flags The array of flag strings.
 * @return true if the character is in the flags list, false otherwise.
 */
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

/**
 * @brief Checks if a string is a valid flag.
 *
 * A valid flag starts with '-' and contains only characters present in the 
 * flags list.
 *
 * @param str The string to check.
 * @param flags The array of flag strings.
 * @return true if the string is a valid flag, false otherwise.
 */
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

/**
 * @brief Checks if a specific flag exists in the command arguments.
 *
 * Iterates through the arguments to determine if the given character is present
 *  in any flag.
 *
 * @param c The flag character to check for.
 * @param flags The array of flag strings.
 * @param args The array of command arguments.
 * @return true if the flag exists, false otherwise.
 */
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

/**
 * @brief Executes the built-in echo command.
 *
 * This function prints the given arguments to the standard output.
 * If the '-n' flag is detected, it suppresses the trailing newline.
 *
 * @param args The array of command arguments.
 * @return Always returns 0.
 */
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
