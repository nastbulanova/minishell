#ifndef MINI_SIGNALS_H
#define MINI_SIGNALS_H

# include <signal.h>


void	setup_signal_handler(void (*handler)(int, siginfo_t *, void *));
void    signal_handler(int signal, siginfo_t *info, void *context);

#endif