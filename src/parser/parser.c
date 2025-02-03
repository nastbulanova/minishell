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

t_parser_error parser(t_minishell *data)
{
	t_token *token;
	int		cmd;

	(data)->exec_data = exec_data_init();
	token = data->token_head;
	while (token)
	{
		cmd = 0;
		if (parser_loop(data, &token, &cmd) != OK)
			return(exec_data_append(&data, 0), syntax_error(&data, &token));
		if (token && token->type == PIPE)
		{
			if (cmd == 0 || !token->next)
				return(exec_data_append(&data, 0), syntax_error(&data, &token));
			else
			{
				exec_data_append(&data, 1);
				cmd = 0;
				token = token->next;
			}
		}
		else
			exec_data_append(&data, 0);
	}
	return(OK);
}
