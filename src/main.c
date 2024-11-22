#include "../inc/minishell.h"


void main_loop(char **envp)
{
    (void)envp;

	char *input;
    int i;

    while (TRUE)
    {
        set_state_signal_handlers(MAIN);
        input = readline("minishell> ");
		if (!input)
        {
            printf("exit\n");
            break;
        }
        char **split = NULL; 
        split = ft_split(input, ' ');
        if (split)
        {
            if (split[0] && ft_strncmp("echo", split[0], 4) == 0)
                cmd_echo(split);
            i = 0;
            while (split[i])
            {
                free(split[i]);
                i++;
            }
            free(split);
        }   
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
    main_loop(envp);
	return (0);
}