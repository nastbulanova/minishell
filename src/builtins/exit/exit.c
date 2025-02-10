/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:57:16 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:57:43 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

bool	arg_numeric(char *arg)
{
	int	x;

	x = 0;
	while (arg[x] == '-' || arg[x] == '+')
		x++;
	if (x > 1 || arg[x] == '\0')
		return (false);
	while (arg[x])
	{
		if (!ft_isdigit(arg[x]))
			return (false);
		x++;
	}
	return (true);
}

static int	handle_more(char **args)
{
	if (!arg_numeric(args[1]))
	{
		minishell_exit(built_exit_string(args[1]), 2, STDERR_FILENO, false);
		return (2);
	}
	else
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
}

static void	handle_one(char **args)
{
	t_minishell	*data;

	data = get_shell(false);
	if (arg_numeric(args[1]))
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		data->exit_code = ft_exit_atoi(args[1]);
		minishell_exit(NULL, data->exit_code, STDOUT_FILENO, false);
	}
	else
		minishell_exit(built_exit_string(args[1]), 2, STDERR_FILENO, false);
}

int	cmd_exit(char **args)
{
	int	args_size;
	int	exit_code;

	exit_code = 0;
	args_size = array_size(args) - 1;
	if (args_size == 0)
		minishell_exit("exit\n", exit_code, STDOUT_FILENO, false);
	else if (args_size == 1)
		handle_one(args);
	else if (args_size > 1)
		return (handle_more(args));
	return (0);
}
