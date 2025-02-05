#include "../../inc/minishell.h"

t_parser_error parser_loop(t_minishell *data, t_token **token, int *cmd)
{
	char	*tmp;
	t_parser_error	error;

	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type >= WORD && (*token)->type <= EXP_FIELD)
		{
			tmp = opt_check(&data, &token);
			if (*cmd == 0)
				error = cmd_check(&data, tmp, &cmd);
			error = opt_add(&data, tmp);
			tmp = NULL;
		}
		else if ((*token)->type >= REDIR_OUT && (*token)->type <= REDIR_APPEND)
			error = redir_check(&data, &token);
		else
			error = heredoc_check(&data, &token);
		if (error == OK)
			*token = (*token)->next;
		else
			return(error);
	}
	return(error);
}

static t_parser_error handle_pipe(t_minishell *data, t_token **token, int *cmd)
{
	if (token && *token && (*token)->type == PIPE)
	{
		if (*cmd == 0 || !(*token)->next)
			return(SYNTAX_ERROR);
		else
		{
			cmd = 0;
			(*token) = (*token)->next;
			return(exec_data_append(&data, 1));
		}
	}
	else
		return(exec_data_append(&data, 0));
}

t_parser_error parser(t_minishell *data)
{
	t_token 	*token;
	int			cmd;
	t_parser_error	error;

	(data)->exec_data = exec_data_init();
	token = data->token_head;
	while (token)
	{
		cmd = 0;
		error = OK;
		error = parser_loop(data, &token, &cmd);
		if (error == SYNTAX_ERROR)
			return(syntax_error(&data, &token));
		else if (error == MALLOC_ERROR)
			return(memory_error(&data));
		else
		{
			error = handle_pipe(data, &token, &cmd);
			if (error == SYNTAX_ERROR)
				return(syntax_error(&data, &token));
			if (error == MALLOC_ERROR)
				return(memory_error(&data));
		}
	}
	return(OK);
}
