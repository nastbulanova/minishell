# include "minishell.h"

t_parser_error	while_sequence(t_token **token_head, char *line, int (*func)(int), int **i)
{
	int	start;
	int	len;
	int	type;

	start = **i;
	len = 0;
	while (func(line[**i]))
	{
		len++;
		(**i)++;
	}
	if (func == ft_iswordchar)
		type = WORD;
	//if (func == ft_isenvvar)
	//	type = 2;
	return(token_add(&token_head, &(line[start]), len, type));
}

t_parser_error	find_field(t_token **token_head, char *line, int (*func)(int), int **i)
{
	int	start;
	int	len;
	int	secondquote;

	(**i)++;
	start = **i;
	len = 0;
	secondquote = 0;
	while (line[**i] != '\0')
	{
		if (func(line[**i]))
		{
			secondquote = 1;
			break ;
		}
		len++;
		(**i)++;
	}
	if (!secondquote)
		return(SYNTAX_ERROR);
	if (func == ft_isquote)
		return((**i)++, token_add(&token_head, &(line[start]), len, FIELD));
	else
		return((**i)++, token_add(&token_head, &(line[start]), len, EXP_FIELD));
}

t_parser_error	find_redir(t_token **token_head, char *line, char c, int **i)
{
	t_token_type	type;
	int 			start;

	start = **i;
	if (c == '>')
		type = REDIR_OUT;
	else
		type = REDIR_IN;
	if (line[**i + 1] == c)
	{
		(**i) += 2;
		return(token_add(&token_head, &(line[start]), 2, type + 2));
	}
	else
	{
		(**i)++;
		return(token_add(&token_head, &(line[start]), 1, type));
	}
}
