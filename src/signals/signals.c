/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:55:39 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:00:11 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handler(int signo, siginfo_t *info, void *context)
{
	t_minishell	*data;

	(void)info;
	(void)context;
	data = get_shell(false);
	if (signo == SIGINT)
	{
		data->exit_code = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	here_doc_handler(int signal, siginfo_t *info, void *context)
{
	t_minishell	*data;

	(void)info;
	(void)context;
	data = get_shell(false);
	if (signal == SIGINT)
		data->exit_code = 130;
}
