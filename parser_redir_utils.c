# include "minishell.h"

char	*file_name_check(t_minishell *data, t_token **token)
{
	if ((*token)->next)
	{
		*token = (*token)->next;
		if ((*token)->type == 1)
			return(ft_substr((*token)->start, 0, (*token)->len));
		else if ((*token)->type == 2)
			return(env_var_replace(data, ft_substr((*token)->start, 0, (*token)->len)));
		else if ((*token)->type == 3)
			return(ft_substr((*token)->start, 0, (*token)->len));
		else if ((*token)->type == 4)
			return(open_field(data, *token));
		else
			return (NULL);/////////////here should be error_func "minishell: parse error near '\n'"
	}
	else
		return (NULL);////////////////here should be error_func "minishell: parse error near '\n'"
}

void	redir_check(t_minishell **data, t_token **token)
{
	if ((*token)->type == 5)
	{
		(*data)->exec_data->new_outfile = file_name_check(*data, token);
		printf("redir type new_out filename %s", (*data)->exec_data->new_outfile);
	}
	else if ((*token)->type == 6)
	{
		(*data)->exec_data->infile = file_name_check(*data, token);
		printf("redir type infile filename %s", (*data)->exec_data->infile);
	}	
	else
	{
		(*data)->exec_data->exist_outfile = file_name_check(*data, token);
		printf("redir type exist_out filename %s", (*data)->exec_data->exist_outfile);
	}
}