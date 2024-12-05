#include "../inc/minishell.h"
# include "../inc/builtins.h"
# include "../inc/env.h"

t_minishell *get_shell(t_env *env)
{
    static t_minishell *data;
    if (env)
        data->env = env;
    return (data);

}
t_minishell *init_shell()
{
    t_minishell *shell;

    shell = safe_malloc(sizeof(t_minishell), "init_shell in main.c");
    shell->env = NULL;
    shell->exp = NULL;
    shell->exec_data = NULL;
    shell->exit_code = 0;
    shell->token_head = NULL;
    
    return (shell);
}
void main_loop(t_minishell *data)
{
	char *input;
    int i;

    env_print(data->env);
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
                cmd_echo(split, STDOUT_FILENO, data);
            else if (split[0] && ft_strncmp("pwd", split[0], 4) == 0)
                cmd_pwd(STDOUT_FILENO, data);
            else if (split[0] && ft_strncmp("cd", split[0], 3) == 0)
                cmd_cd(split, STDOUT_FILENO, data);
            else if (split[0] && ft_strncmp("env", split[0], 4) == 0)
                env_print(data->env);
            else if (split[0] && ft_strncmp("export", split[0], 7) == 0)
                cmd_export(split, STDOUT_FILENO, data);
            else if (split[0] && ft_strncmp("clear", split[0], 6) == 0)
                printf("\033[H\033[J");
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
    if (data)
        minishell_free(data);
}


int	main(int argc, char **argv, char **envp)
{
	t_minishell *data;
    (void)argv;
    data = init_shell(); 
    if (argc != 1)
        error_exit(RB "Minishell takes no arguments. Exiting." RST, "main in main.c");
    if (!*envp)
    {
		ft_putendl_fd(RB "No environment variables found." RST, STDOUT_FILENO);
        ft_putendl_fd(GB "Initializing defaults." RST, STDOUT_FILENO);
        env_init_default(data);
    }
    
    env_init(argv, envp, data);
    exp_init(data);
    display_splash_screen();
    main_loop(data);
    
    return (0);
}