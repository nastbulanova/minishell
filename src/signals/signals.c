#include "../../inc/minishell.h"

void signal_handler(int signal, siginfo_t *info, void *context)
{
	pid_t pid_to_kill;
	int status;
	(void)context;
	(void)info;
    if (signal == SIGINT) 
	{
        printf("\nCaught Ctrl-C (SIGINT).\n");
		if (global_shell.process_head)
		{
			//kill the first process found (most recent if LIFO is implemented)
			pid_to_kill = global_shell.process_head->pid;
			if (kill(global_shell.process_head->pid, SIGINT) == -1)
			{
				//the signal failed. idk if it's possible to do anything in this case (maybe implemente a retry?!)
			}
			else
			{
				waitpid(pid_to_kill, &status, 0);
				remove_process(pid_to_kill);
			}
			//wait for exit?!
			//remove node
		}
    }
    else if (signal == SIGQUIT) 
	{
        printf("\nCaught Ctrl-\\ (SIGQUIT)\n");
    }
}


void	setup_signal_handler(void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	sa;

	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}