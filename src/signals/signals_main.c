/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:55:39 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:02:08 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	set_state_signal_handlers(enum e_signal_state state)
{
	static struct sigaction	sa;

	if (state == MAIN)
		set_signal_main(sa);
	else if (state == CHILD)
		set_signal_child(sa);
	else if (state == HERE_DOC)
		set_signal_here_doc(sa);
}

void	set_signal_main(struct sigaction sa)
{
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGINT, &sa, NULL);
	set_sig_ignore(&sa, SIGQUIT);
}

void	set_signal_child(struct sigaction sa)
{
	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_signal_here_doc(struct sigaction sa)
{
	sa.sa_sigaction = here_doc_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction(SIGINT, &sa, NULL);
	set_sig_ignore(&sa, SIGQUIT);
}

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
