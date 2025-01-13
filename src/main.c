# include "../inc/minishell.h"



t_minishell *get_shell(bool init)
{
    static t_minishell data;
    if (init)
    {
        //data = safe_malloc(sizeof(t_minishell), "init_shell in main.c");
        data.env = NULL;
        data.exec_data = NULL;
        data.exit_code = 0;
        data.token_head = NULL;
        data.prompt = NULL;
    }
    return (&data);
}
t_minishell *init_shell()
{
    t_minishell *data;

    data = safe_malloc(sizeof(t_minishell), "init_shell in main.c");
    data->env = NULL;
    data->exec_data = NULL;
    data->exit_code = 0;
    data->token_head = NULL;
    return (data);
}
void main_loop(t_minishell *data)
{
    char *input;
    t_exec_data *command_list; 
    command_list = NULL;
    set_state_signal_handlers(MAIN);
    while (TRUE)
    {
        update_prompt(data);
        input = readline(data->prompt);
        if (!input) 
        {
            printf("exit\n");
            break; 
        }
        add_history(input);
        if (c_strcmp("run test0", input) == 0)
            command_list = get_test(0);
        if (c_strcmp("run test1", input) == 0)
            command_list = get_test(1);
        if (c_strcmp("run test2", input) == 0)
            command_list = get_test(2);
        if (c_strcmp("run test3", input) == 0)
            command_list = get_test(3);
        if (c_strcmp("run test4", input) == 0)
            command_list = get_test(4);
        if (c_strcmp("run test5", input) == 0)
            command_list = get_test(5);
        if (c_strcmp("run test6", input) == 0)
            command_list = get_test(6);
        if (c_strcmp("run test7", input) == 0)
            command_list = get_test(7);
        if (c_strcmp("run test8", input) == 0)
            command_list = get_test(8);
        if (c_strcmp("run test9", input) == 0)
            command_list = get_test(9);
        if (c_strcmp("run test10", input) == 0)
            command_list = get_test(10);
        if (command_list)
        {
            execute_command(command_list, env_to_array(data->env));
            free_exec_data_list(command_list);
            command_list = NULL;
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