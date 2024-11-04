#include "../inc/minishell.h"


void main_loop(char **envp)
{
    (void)envp;

	char *input;
    while (TRUE)
    {
        input = readline("minishell> ");
		if (!input)
        {
            printf("exit\n");
            break;
        }
		printf("You entered: %s\n", input);
		free(input);
    }
}


int	main(int argc, char **argv, char **envp)
{
	
	(void)argv;
    if (argc != 1)
    {
		ft_putendl_fd("Minishell takes no arguments. Exiting.", STDERR_FILENO);
        return (1);
    }
    if (!*envp)
    {
		ft_putendl_fd("No environment variables found. Exiting.", STDERR_FILENO);
        return (1);
    }
    //setup_signal_handling();
    main_loop(envp);
	return (0);
}