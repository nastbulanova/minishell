/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:55:21 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 12:55:22 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
	{
		ft_putstr_fd("Malloc failure\n", STDERR_FILENO);
		return (NULL);
	}
	ft_memset(ret, 0, bytes);
	return (ret);
}

void	error_exit(const char *error, const char *function_name)
{
	t_minishell	*data;

	data = get_shell(NULL);
	ft_putstr_fd(RB "", STDERR_FILENO);
	ft_putstr_fd((char *)error, STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	ft_putstr_fd((char *)function_name, STDERR_FILENO);
	ft_putstr_fd("\n" RST, STDERR_FILENO);
	minishell_free(data);
	exit(EXIT_FAILURE);
}

void	minishell_free(t_minishell *data)
{
	if (data)
	{
		if (data->prompt)
			free(data->prompt);
		if (data->env)
			env_free(data->env);
		if (data->list_exec_data)
			free_parser_data(&data);
		if (data->exec_env)
			free_array(data->exec_env, NULL);
		close_pipe(data->heredoc_pipe);
	}
	clear_history();
}
