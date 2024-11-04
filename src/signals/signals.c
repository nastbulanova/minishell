#include "../../inc/minishell.h"

void set_state_signal_handlers(enum e_signal_state state)
{
    static struct sigaction sa;
    
    if (state == MAIN)
    {
        set_signal_main(sa);
    }
    else if (state == CHILD)
    {
        set_signal_child(sa);
    }
    else if (state == HERE_DOC)
    {
        set_signal_here_doc(sa);
    }
}

void	set_signal_main(struct sigaction sa)
{
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) != 0)
		return ;
	sigaction (SIGINT, &sa, NULL);
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

void	handler(int signo, siginfo_t *info, void *context)
{
	t_shell_info	sinfo;

	(void)info;
	(void)context;
	sinfo = get_shell_info();
	if (signo == SIGINT)
	{
		sinfo.exit_code = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	(void)sinfo;
}

void	here_doc_handler(int signal, siginfo_t *info, void *context)
{
	t_shell_info	sinfo;

	(void)info;
	(void)context;
	sinfo = get_shell_info();
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		sinfo.exit_code = 130;
	}
	(void)sinfo;
}

t_shell_info get_shell_info()
{
	static t_shell_info	sinfo;
	return (sinfo);
}