#include "../inc/minishell.h"
t_shell_main global_shell;


int	main(int argc, char **argv, char **envp)
{
	global_shell.process_head = NULL;
	setup_signal_handler(signal_handler);

	while (1)
		pause();
	return (0);
}