#include "minishell.h"

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

void    print_token(t_token *token)
{
	while (token)
	{
		printf("token %s\n", token->start);
		printf("len %d\n", token->len);
		printf("type %d\n", token->type);
		//printf("group %d\n\n", token->group);
		token = token->next;
   }
}
t_minishell *data_init()
{
	t_minishell	*data;

	data = (t_minishell *)malloc(sizeof(t_minishell));
	if (!data)
		return (NULL);/////////////////////////////////// error_func
	data->list_exec_data = NULL;
	data->token_head = NULL;
	return(data);
}


int main(int argc, char **argv, char **env)
{
	//char    *line = " > 1 | wc";
	//char    *line = "<";
	char    *line = "echo -n  << delim > $UNDEFINED_VAR > outfile | wc -l < text";

	t_minishell *data;
	t_minishell	**data_ptr;

	//t_token		*tmp;
	t_env		*tmp1;

	(void)argc;
	(void)argv;

	data = data_init();
	//line = readline("minishell> ");
	if (lexer(data, line) != 0)
	{
		free(data);
		exit(0);
	}
	//print_token(data->token_head);
	data->exit_code = 777;////////////////////////////////////
	printf("token list created\n");
	data->env = env_to_linked_list(env);
	parser(data);
	print_exec_data(data);
	
	while (data->env)
	{
		tmp1 = data->env;
		data->env = data->env->next;
		free(tmp1->name);
		free(tmp1->value);
		free(tmp1);
	}
	data_ptr = &data;
	//data_ptr_ptr = &data_ptr;
	free_parser_data(&data_ptr);
	free(data);
	return(0);
}