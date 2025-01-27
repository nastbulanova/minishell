# include "../inc/minishell.h"

t_minishell *get_shell(bool init)
{
    static t_minishell data;
    if (init)
    {
        data.env = NULL;
        data.exec_data = NULL;
        data.exit_code = 0;
        data.token_head = NULL;
        data.prompt = NULL;
        data.heredoc_pipe[0] = -1;
        data.heredoc_pipe[1] = -1;

    }
    return (&data);
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
        if (c_strcmp("run test11", input) == 0)
            command_list = get_test(11);
        if (c_strcmp("run test12", input) == 0)
            command_list = get_test(12);
        if (c_strcmp("run test13", input) == 0)
            command_list = get_test(13);
        if (c_strcmp("run test14", input) == 0)
            command_list = get_test(14);
        if (c_strcmp("run test15", input) == 0)
            command_list = get_test(15);
        if (c_strcmp("run test16", input) == 0)
            command_list = get_test(16);
        if (c_strcmp("run test17", input) == 0)
            command_list = get_test(17);
        if (c_strcmp("run test18", input) == 0)
            command_list = get_test(18);
        if (c_strcmp("run test19", input) == 0)
            command_list = get_test(19);
        if (c_strcmp("run test20", input) == 0)
            command_list = get_test(20);
        if (c_strcmp("run test21", input) == 0)
            command_list = get_test(21);
        if (c_strcmp("run test22", input) == 0)
            command_list = get_test(22);
        if (c_strcmp("run test23", input) == 0)
            command_list = get_test(23);
        if (c_strcmp("run test24", input) == 0)
            command_list = get_test(24);
        if (c_strcmp("run test25", input) == 0)
            command_list = get_test(25);
        if (c_strcmp("run test26", input) == 0)
            command_list = get_test(26);
        if (c_strcmp("run test27", input) == 0)
            command_list = get_test(27);
        if (c_strcmp("run test28", input) == 0)
            command_list = get_test(28);
        if (c_strcmp("run test29", input) == 0)
            command_list = get_test(29);
        if (c_strcmp("run test30", input) == 0)
            command_list = get_test(30);
        if (c_strcmp("run test31", input) == 0)
            command_list = get_test(31);
        if (c_strcmp("run test32", input) == 0)
            command_list = get_test(32);
        if (c_strcmp("run test33", input) == 0)
            command_list = get_test(33);
        if (c_strcmp("run test34", input) == 0)
            command_list = get_test(34);
        if (c_strcmp("run test35", input) == 0)
            command_list = get_test(35);
        if (c_strcmp("run test36", input) == 0)
            command_list = get_test(36);
        if (c_strcmp("run test37", input) == 0)
            command_list = get_test(37);
        if (c_strcmp("run test38", input) == 0)
            command_list = get_test(38);
        if (c_strcmp("run test39", input) == 0)
            command_list = get_test(39);
        if (c_strcmp("run test40", input) == 0)
            command_list = get_test(40);
        if (c_strcmp("run test41", input) == 0)
            command_list = get_test(41);
        if (c_strcmp("run test42", input) == 0)
            command_list = get_test(42);
        if (c_strcmp("run test43", input) == 0)
            command_list = get_test(43);
        if (c_strcmp("run test44", input) == 0)
            command_list = get_test(44);
        if (c_strcmp("run test45", input) == 0)
            command_list = get_test(45);
        if (c_strcmp("run test46", input) == 0)
            command_list = get_test(46);
        if (c_strcmp("run test47", input) == 0)
            command_list = get_test(47);
        if (c_strcmp("run test48", input) == 0)
            command_list = get_test(48);
        if (c_strcmp("run test49", input) == 0)
            command_list = get_test(49);
        if (c_strcmp("run test50", input) == 0)
            command_list = get_test(50);
        if (c_strcmp("run test51", input) == 0)
            command_list = get_test(51);
        if (c_strcmp("run test52", input) == 0)
            command_list = get_test(52);
        if (c_strcmp("run test53", input) == 0)
            command_list = get_test(53);
        if (c_strcmp("run test54", input) == 0)
            command_list = get_test(54);
        if (c_strcmp("run test55", input) == 0)
            command_list = get_test(55);
        if (c_strcmp("run test56", input) == 0)
            command_list = get_test(56);
        if (c_strcmp("run test57", input) == 0)
            command_list = get_test(57);
        if (c_strcmp("run test58", input) == 0)
            command_list = get_test(58);
        if (c_strcmp("run test59", input) == 0)
            command_list = get_test(59);
        if (c_strcmp("run test60", input) == 0)
            command_list = get_test(60);
        if (c_strcmp("run test61", input) == 0)
            command_list = get_test(61);
        if (c_strcmp("run test62", input) == 0)
            command_list = get_test(62);
        if (c_strcmp("run test63", input) == 0)
            command_list = get_test(63);
        if (c_strcmp("run test64", input) == 0)
            command_list = get_test(64);
        if (c_strcmp("run test65", input) == 0)
            command_list = get_test(65);
        if (c_strcmp("run test66", input) == 0)
            command_list = get_test(66);
        if (c_strcmp("run test67", input) == 0)
            command_list = get_test(67);
        if (c_strcmp("run test68", input) == 0)
            command_list = get_test(68);
        if (c_strcmp("run test69", input) == 0)
            command_list = get_test(69);
        if (c_strcmp("run test70", input) == 0)
            command_list = get_test(70);
        if (c_strcmp("run test71", input) == 0)
            command_list = get_test(71);
        if (c_strcmp("run test72", input) == 0)
            command_list = get_test(72);
        if (c_strcmp("run test73", input) == 0)
            command_list = get_test(73);
        if (c_strcmp("run test74", input) == 0)
            command_list = get_test(74);
        if (c_strcmp("run test75", input) == 0)
            command_list = get_test(75);
        if (c_strcmp("run test76", input) == 0)
            command_list = get_test(76);
        if (c_strcmp("run test77", input) == 0)
            command_list = get_test(77);
        if (c_strcmp("run test78", input) == 0)
            command_list = get_test(78);
        if (c_strcmp("run test79", input) == 0)
            command_list = get_test(79);
        if (c_strcmp("run test80", input) == 0)
            command_list = get_test(80);
        if (c_strcmp("run test81", input) == 0)
            command_list = get_test(81);
        if (c_strcmp("run test82", input) == 0)
            command_list = get_test(82);
        if (c_strcmp("run test83", input) == 0)
            command_list = get_test(83);
        if (c_strcmp("run test84", input) == 0)
            command_list = get_test(84);
        if (c_strcmp("run test85", input) == 0)
            command_list = get_test(85);
        if (c_strcmp("run test86", input) == 0)
            command_list = get_test(86);
        if (c_strcmp("run test87", input) == 0)
            command_list = get_test(87);
        if (c_strcmp("run test88", input) == 0)
            command_list = get_test(88);
        if (c_strcmp("run test89", input) == 0)
            command_list = get_test(89);
        if (c_strcmp("$?", input) == 0)
            ft_printf("Exit Code: %d\n", data->exit_code);
        if (command_list)
        {
            data->exit_code = 0;
            execute_command_list(data, command_list, env_to_array(data->env));
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