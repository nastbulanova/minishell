#include "minishell.h"

void	exec_data_init(t_exec_data	**exec_data)
{
	*exec_data = (t_exec_data *)malloc(sizeof(t_exec_data));
	if (!(*exec_data))
		return ;////////////////////////error_func
	(*exec_data)->cmd = NULL;
	(*exec_data)->opt = NULL;
	(*exec_data)->env = NULL;
	(*exec_data)->is_pipe = -1;
	(*exec_data)->infile = NULL;
	(*exec_data)->new_outfile = NULL;
	(*exec_data)->exist_outfile = NULL;
}

void	group_init(t_token  **token_head)
{
	int		group;
	t_token	*current;

	group = 0;
	current = *token_head;
	while (current)
	{
		if (current->prev)
		{
			if (current->prev->prev)
			{
				if (current->prev->prev->type >= 5 && current->prev->prev->type <= 9)
					group++;
			}
		}
		current->group = group;
		current = current->next;
	}
}

void	check_context(t_minishell *data, t_token **token, int *i)
{
	(void)data;/////////////////////////////////////////////////////
	if (*token)
	{
		if (!(*token)->next)
		{
			//do_cmd(data->exec_data);//////////////////piping, redir, execve
			exit(0);////////////////////////////////////////////////////to delete
		}
		else if ((*token)->next->group > (*token)->group)
		{
			//do_cmd(data->exec_data);//////////////////piping, redir, execve
			exit(0);////////////////////////////////////////////////////to delete
			(*token) = (*token)->next;
			*i = START;
		}
		else if (i == START)
		{
			(*token) = (*token)->next;
			(*i)++;
		}
	}
	else
		//do_cmd(data->exec_data);//////////////////piping, redir, execve
		exit(0);
}

void	parse_start(t_minishell **data, t_token **token, int *i)
{
	if ((*token)->type == 1)
	{
		(*data)->exec_data->cmd = cmd_check(*token, (*data)->env);
		*i = AFTERCMD;
	}
	else if ((*token)->type == 2)
	{
		env_var_replace(*data, ft_substr((*token)->start, 0, (*token)->len));
	}
	else if ((*token)->type >= 5 || (*token)->type <=7)
	{
		redir_check(data, token);
		*i = START;
	}
	else if ((*token)->type == 8)
	{
		here_doc_start(&data, token);// fork
		*i = START;
	}
	else if ((*token)->type == 9)
	{
		////////////////////////////////// error : syntax error near unexpected token `|'
		*i = START;
	}
}

void	parse_after_cmd()
{
	if (token->type >= 1 && token->type <= 4)
		opt_check(&data, &token);
	else if (token->type >= 5 || token->type <=7)
		redir_check(&data, &token);
	else if (token->type == 8)
		here_doc_start(&data, &token);
	else if (token->type == 9)
		data->exec_data->is_pipe = 1;
}

int	parser(t_minishell *data)
{
	t_token		*token;
	int			i;

	exec_data_init(&(data)->exec_data);
	group_init(&(data)->token_head);
	print_token(data->token_head);///////////////////////////////////to delete
	token = data->token_head;
	i = 0;
	while (token)
	{
		if (i == START)
			parse_start();
		else if (i == AFTERCMD)
			parse_after_cmd();
		else if (i = AFTEROPT)
			if (token->type == 5)
			{
				// find a filename, put to struct new_outfile 
				check_context(data, &token, &i);
			}
			else if (token->type == 6)
			{
				// find a filename, put to struct infile
				check_context(data, &token, &i);
			}
			else if (token->type == 7)
			{
				// find a filename, put to struct exist_outfile
				check_context(data, &token, &i);
			}
			else if (token->type == 8)
			{
				// find a filename, put to struct here_doc
				check_context(data, &token, &i);
			}
			else if (token->type == 9)
			{
				// put to struct is_pipe
				check_context(data, &token, &i);
			}
		}*/
		printf("**********end\n");
	}
	return (0);
}
