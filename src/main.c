#include "../inc/minishell.h"
#include "../inc/builtins.h"

t_minishell *init_shell()
{
    t_minishell *shell;

    shell = malloc(sizeof(t_minishell));
    if (!shell)
        return (NULL);
    shell->env = NULL;
    shell->exec_data = NULL;
    shell->exit_code = 0;
    shell->token_head = NULL;
    return (shell);
}
void main_loop(char **envp)
{
    (void)envp;
    t_minishell *shell;

    shell = init_shell();
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
            if (split[0] && ft_strncmp("echo", split[0], 5) == 0)
                cmd_echo(split, STDOUT_FILENO, shell);
            else if (split[0] && ft_strncmp("pwd", split[0], 5) == 0)
                cmd_pwd(split, STDOUT_FILENO, shell);
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