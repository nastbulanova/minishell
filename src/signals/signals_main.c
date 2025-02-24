/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:55:39 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/24 13:52:48 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @file signals_main.c
 * @brief Signal handling functions for Minishell.
 */

/**
 * @brief Sets the appropriate signal handlers based on the given state.
 *
 * This function configures signal handlers depending on whether the shell
 * is in the main execution state, handling a child process, or processing
 * a here-document.
 *
 * @param state The signal state to be set (MAIN, CHILD, or HERE_DOC).
 */
void	set_state_signal_handlers(enum e_signal_state state)
{
	static struct sigaction	sa;

	if (state == MAIN)
		set_signal_main(sa);
	else if (state == CHILD)
		set_signal_child(sa);
	else if (state == HERE_DOC)
		set_signal_here_doc(sa);
	else if (state == IGNORE)
		set_signal_ignore(sa);
}

/**
 * @brief Configures signal handling for the main shell process.
 *
 * This function sets up the signal handlers for SIGINT and SIGQUIT,
 * defining a custom handler for SIGINT and ignoring SIGQUIT.
 *
 * @param sa The sigaction structure used to set up the handlers.
 */
void	set_signal_main(struct sigaction sa)
{
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGINT, &sa, NULL);
	set_sig_ignore(&sa, SIGQUIT);
}

/**
 * @brief Configures default signal handling for child processes.
 *
 * Sets SIGINT and SIGQUIT to their default behaviors for child processes.
 *
 * @param sa The sigaction structure used to set up the handlers.
 */
void	set_signal_child(struct sigaction sa)
{
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/**
 * @brief Configures signal handling for here-document input.
 *
 * This function sets up the SIGINT handler for handling interruptions
 * while reading a here-document and ignores SIGQUIT.
 *
 * @param sa The sigaction structure used to set up the handlers.
 */
void	set_signal_here_doc(struct sigaction sa)
{
	sa.sa_sigaction = here_doc_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGINT, &sa, NULL);
	set_sig_ignore(&sa, SIGQUIT);
}

/**
 * @brief Configures a signal to be ignored.
 *
 * This function modifies the given sigaction structure to ignore 
 * a specific signal
 * and preserves the original signal action configuration.
 *
 * @param sa Pointer to the sigaction structure to modify.
 * @param signal The signal number to be ignored.
 */
void	set_sig_ignore(struct sigaction *sa, int signal)
{
	struct sigaction	sa_origin;
	int					sa_origin_flags;

	sa_origin_flags = sa->sa_flags;
	sa->sa_handler = SIG_IGN;
	sa->sa_flags |= SA_SIGINFO;
	if (sigemptyset(&sa->sa_mask) != 0)
		return ;
	sigaction(signal, sa, &sa_origin);
	sa->sa_flags = sa_origin_flags;
}
