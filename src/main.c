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
    t_extended_exec_data *command_list; 
    command_list = mock_parser(data);
    set_state_signal_handlers(MAIN);
    while (TRUE)
    {
        update_prompt(data);
        input = readline(data->prompt);
        
        printf("Input pointer: %p\n", input);
        printf("Prompt: %s\n", data->prompt);
        if (!input) 
        {
            printf("exit\n");
            break; 
        }
        if (command_list)
            execute_command(command_list, data);
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
    rl_initialize();
    main_loop(data);
    
    return (0);
}