#ifndef MINI_SIGNALS_H
#define MINI_SIGNALS_H

# include <signal.h>



enum e_signal_state
{
    MAIN,
    CHILD,
    HERE_DOC
};

typedef struct s_shell_info
{
    int		exit_code;

}t_shell_info;

void            set_state_signal_handlers(enum e_signal_state state);
void	        set_signal_main(struct sigaction sa);
void	        set_signal_child(struct sigaction sa);
void	        set_signal_here_doc(struct sigaction sa);
void	        set_sig_ignore(struct sigaction *sa, int signal);
void	        here_doc_handler(int signal, siginfo_t *info, void *context);
void	        handler(int signo, siginfo_t *info, void *context);
t_shell_info    get_shell_info();

#endif