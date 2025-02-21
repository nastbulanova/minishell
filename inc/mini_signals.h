/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_signals.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:36:38 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/20 14:24:29 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SIGNALS_H
# define MINI_SIGNALS_H

# include "defines.h"
# include "structs.h"
# include <signal.h>

void	set_state_signal_handlers(enum e_signal_state state);
void	set_signal_main(struct sigaction sa);
void	set_signal_child(struct sigaction sa);
void	set_signal_here_doc(struct sigaction sa);
void	set_signal_ignore(struct sigaction sa);
void	set_sig_ignore(struct sigaction *sa, int signal);
void	here_doc_handler(int signal, siginfo_t *info, void *context);
void	handler(int signo, siginfo_t *info, void *context);

#endif