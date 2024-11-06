#include "minishell.h"

void    print_token(t_token *token)
{
	while (token)
	{
		printf("token %s\n", token->start);
		printf("len %d\n", token->len);
		printf("type %d\n", token->type);
		printf("group %d\n\n", token->group);

		token = token->next;
   }
}
t_minishell *data_init()
{
	t_minishell	*data;

	data = (t_minishell *)malloc(sizeof(t_minishell));
	if (!data)
		return (NULL);/////////////////////////////////// error_func
	return(data);
}


int main(int argc, char **argv, char **env)
{
	//char    *line = "ls 'dog' | \"wc\" > 1.txt << \0";
	char    *line = "wc > 1.txt";

	t_minishell *data;
	t_token		*tmp;

	(void)argc;
	(void)argv;

	data = data_init();
	//line = readline("minishell> ");
	data->token_head = lexer(line);
	data->env = env;
	parser(data);
	//free(data->exec_data);
	while (data->token_head)
	{
		tmp = data->token_head;
		data->token_head = data->token_head->next;
		free(tmp);
	}
	free(data);
	return(0);
}