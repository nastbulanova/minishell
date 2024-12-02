#include "../inc/minishell.h"
# include "../inc/builtins.h"
# include "../inc/env.h"

t_minishell *get_shell(t_env *env)
{
    static t_minishell *shell;
    if (env)
        shell->env = env;
    return (shell);

}
t_minishell *init_shell()
{
    t_minishell *shell;

    shell = safe_malloc(sizeof(t_minishell), "init_shell in main.c");
    shell->env = NULL;
    shell->exec_data = NULL;
    shell->exit_code = 0;
    shell->token_head = NULL;
    
    return (shell);
}
void main_loop(t_minishell *shell)
{
	char *input;
    int i;

    //DEBUG ONLY env_print(shell->env);
    set_state_signal_handlers(MAIN);
    while (TRUE)
    {
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
                cmd_cd(split, STDOUT_FILENO, shell);
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
	t_minishell *shell;
    (void)argv;
    shell = init_shell(); 
    if (argc != 1)
        error_exit(RB "Minishell takes no arguments. Exiting." RST, "main in main.c");
    if (!*envp)
    {
		ft_putendl_fd(RB "No environment variables found." RST, STDOUT_FILENO);
        ft_putendl_fd(GB "Initializing defaults." RST, STDOUT_FILENO);
        env_init_default(shell);
    }
    
    env_init(argv, envp, shell);
    main_loop(shell);
    
    return (0);
}