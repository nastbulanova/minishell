/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:55:39 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/24 13:53:09 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * @file signals.c
 * @brief Signal handling functions for Minishell.
 *
 * This file contains functions to handle signals such as SIGINT
 * during normal shell operation and within heredoc mode.
 */

void	set_signal_ignore(struct sigaction sa)
{
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	set_sig_ignore(&sa, SIGINT);
	set_sig_ignore(&sa, SIGQUIT);
}

/**
 * @brief Handles signals received by the main shell process.
 *
 * This function is called when the shell receives certain signals,
 * such as SIGINT (Ctrl+C). It updates the shell's state accordingly
 * and ensures proper command line redisplay.
 *
 * @param signo The signal number received.
 * @param info Unused parameter (required by signal handler signature).
 * @param context Unused parameter (required by signal handler signature).
 */
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

/**
 * @brief Handles signals received within a heredoc session.
 *
 * This function is specifically used when the shell is in heredoc mode.
 * It ensures that receiving SIGINT properly updates the shell state
 * without attempting to redisplay the command line.
 *
 * @param signal The signal number received.
 * @param info Unused parameter (required by signal handler signature).
 * @param context Unused parameter (required by signal handler signature).
 */
void	here_doc_handler(int signal, siginfo_t *info, void *context)
{
	t_minishell	*data;

	(void)info;
	(void)context;
	data = get_shell(false);
	if (signal == SIGINT)
		data->exit_code = 130;
}
