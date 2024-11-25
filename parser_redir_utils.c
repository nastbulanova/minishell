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
			return (NULL);/////////////here should be error_func "minishell: : syntax error near unexpected token `newline'
	}
	else
		return (NULL);////////////////here should be error_func "minishell: syntax error near unexpected token `newline'
}

void	redir_check(t_minishell **data, t_token **token)
{
	if ((*token)->type == 5)
	{
		(*data)->exec_data->new_outfile = file_name_check(*data, token);
		//////if (!) add error messages for all the cases
		printf("redir type new_out filename %s", (*data)->exec_data->new_outfile);/////////////// to delete
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

int	line_read(char *delim, int file)
{
	char	*line;

	line = readline("heredoc> ");
	if (!line)
		return (-1);
	line = ft_strjoin(line, "\n");
	if (!ft_strncmp(line, delim, ft_strlen(delim)))
		return (free(line), -1);
	write(file, &line, ft_strlen(line));
	free(line);
	return (1);
}

void	here_doc_start(t_minishell	**data, t_token **token) 
{
	char	*delim;
	int		file;
	int		go;

//// it should be in a child procces ////////////////////////////////////////////////////////
	if ((*token)->next)
		*token = (*token)->next;
	//else
		////////////////////////// error_func "parse error near '\n'"
	delim = ft_strjoin(ft_substr((*token)->start, 0, (*token)->len), "\n");
	file = open("here_doc", O_WRONLY | O_CREAT | O_APPEND, 0644);
	/*if (!file) 
	{
		//////////////////////////// error_func()
		free(delim);
		return ;
	}*/
	go = 1;
	while (go)
		go = line_read(delim, file);
	free(delim);
	close(file);
}
