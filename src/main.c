# include "../inc/minishell.h"



t_minishell *get_shell(bool init)
{
    static t_minishell *data;
    if (init)
    {
        data = safe_malloc(sizeof(t_minishell), "init_shell in main.c");
        data->env = NULL;
        data->exec_data = NULL;
        data->exit_code = 0;
        data->token_head = NULL;
        data->prompt = NULL;
    }
    return (data);

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
void main_loop(t_minishell *data)
{
	char *input;
    int i;

    set_state_signal_handlers(MAIN);
    while (TRUE)
    {
        update_prompt(data);
        //ft_printf(data->prompt);
        input = readline(data->prompt);
		if (!input)
        {
            printf("exit\n");
            break;
        }
        else
            add_history(input);
        char **split = NULL; 
        split = ft_split(input, ' ');
        if (split)
        {
            if (split[0] && c_strcmp("echo", split[0]) == 0)
                cmd_echo(split, data);
            else if (split[0] && c_strcmp("pwd", split[0]) == 0)
                cmd_pwd(data);
            else if (split[0] && c_strcmp("cd", split[0]) == 0)
                cmd_cd(split, data);
            else if (split[0] && c_strcmp("env", split[0]) == 0)
                cmd_env(split, data);
            else if (split[0] && c_strcmp("export", split[0]) == 0)
                cmd_export(split, data);
            else if (split[0] && c_strcmp("unset", split[0]) == 0)
                cmd_unset(split, data);
            else if (split[0] && c_strcmp("exit", split[0]) == 0)
                cmd_exit(split, data);
            else if (split[0] && c_strcmp("clear", split[0]) == 0)
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

    data = get_shell(true); 
    if (argc != 1)
        error_exit(RB "Minishell takes no arguments. Exiting." RST, "main in main.c");
    if (!*envp)
    {
		ft_putendl_fd(RB "No environment variables found." RST, STDOUT_FILENO);
        ft_putendl_fd(GB "Initializing defaults." RST, STDOUT_FILENO);
        env_init_default(argv, data);
    }
    env_init(argv, envp, data);
    display_splash_screen();
    main_loop(data);
    
    return (0);
}