#include "../inc/minishell.h"
# include "../inc/builtins.h"
# include "../inc/env.h"

t_minishell *init_shell(t_env *env)
{
    t_minishell *shell;

    shell = safe_malloc(sizeof(t_minishell), "init_shell in main.c");
    shell->env = env;
    shell->exec_data = NULL;
    shell->exit_code = 0;
    shell->token_head = NULL;
    
    return (shell);
}
void main_loop(t_env *env)
{
    (void)env;
    t_minishell *shell;
	char *input;
    int i;

    shell = init_shell(env);
    //DEBUG ONLY env_print(shell->env);
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
            else if (split[0] && ft_strncmp("pwd", split[0], 4) == 0)
                cmd_pwd(STDOUT_FILENO, shell);
            else if (split[0] && ft_strncmp("cd", split[0], 3) == 0)
                cmd_pwd(STDOUT_FILENO, shell);
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
    if (shell)
        minishell_free(shell);
}


int	main(int argc, char **argv, char **envp)
{
	
	t_env *env;
    (void)argv;

    env = NULL;
    if (argc != 1)
        error_exit(RB "Minishell takes no arguments. Exiting." RST, "main in main.c");
    if (!*envp)
    {
		ft_putendl_fd(RB "No environment variables found." RST, STDOUT_FILENO);
        ft_putendl_fd(GB "Initializing defaults." RST, STDOUT_FILENO);
        env_init_default(&env);
    }
    
    env_init(argv, envp, &env);
    main_loop(env);
    
    return (0);
}