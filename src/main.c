# include "../inc/minishell.h"

void	print_exec_data(t_minishell *data)
{
	t_exec_data	*tmp;
	//t_opt_llist	*list;
	t_redir		*redirs;
	char	**list;
	int i;
	int j;

	i = 0;
	tmp = data->list_exec_data;
	while (tmp)
	{
		printf("\n*** %d ***\n", i);
		printf("cmd: %s\n", tmp->cmd);
		printf("builtin: %d\n", tmp->is_builtin);
		printf("opt: ");

		/*list = tmp->opt_llist;
		while (list)
		{
			printf("%s ", list->opt);
			list = list->next;
		}*/
		j = 0;
		list = tmp->opt;
		if (list)
		{
			while (list[j])
			{
				printf("%s ", list[j]);
				j++;
			}
		}
		printf("\n");
		printf("redirs:\n");
		redirs = tmp->redirs;
		while (redirs)
		{
			printf("%d ", redirs->type);
			if (redirs->str)
				printf("%s", redirs->str);
			printf("\n");
			redirs = redirs->next;
		}
		tmp = tmp->next;
		i++;
	}
	printf("*** all printed ***\n");

}

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

        if (lexer(data, input) != 0)
	    {
		    free(data);
		    exit(0);
	    }

        printf("token list created\n");
        //data->env = env_to_linked_list(env);
        if (parser(data) == OK)
        {
            print_exec_data(data);
            execute_command_list(data, data->list_exec_data,env_to_array(data->env));
           
            free_parser_data(&data);
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