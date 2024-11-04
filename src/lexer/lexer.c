#include "../../inc/minishell.h"

/*
token types
1 word
2 space
3 field ' '
4 exp_field " "
5 redir_out >
6 redir_in <
7 redir_append >>
8 redir here_doc <<
9 pipe
*/

t_token	*while_sequence(t_token *token_head, char *line, int (*func)(int), int **i)
{
	int	start;
	int	len;
	int	type;

	start = **i;
	len = 0;
	while (line[**i] != '\0' && func(line[**i]))
	{
		len++;
		(**i)++;
	}
	if (func == ft_iswordchar)
		type = 1;
	//if (func == ft_isspace)
	//	type = 2;
	return (token_create(token_head, &(line[start]), len, type));
}

t_token	*find_field(t_token *token_head, char *line, int (*func)(int), int **i)
{
	int	start;
	int	len;
	int	secondquote;

	start = **i;
	(**i)++;
	len = 2;
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
	/*if (!secondquote)
		error*/////////////////////////////////////////////new prompt
	if (func == ft_isquote)
		secondquote = 3;
	if (func == ft_isdblquote)
		secondquote = 4;
	return ((**i)++, token_create(token_head, &(line[start]), len, secondquote));
}

t_token	*find_redir(t_token *token_head, char *line, char c, int **i)
{
	int	type;
	int start;

	start = **i;
	if (c == '>')
		type = 5;
	else
		type = 6;
	if (line[**i + 1] == c)
		return ((**i)++, (**i)++, token_create(token_head, &(line[start]), 2, type + 2));
	else
		return ((**i)++, token_create(token_head, &(line[start]), 1, type));
}

t_token	*check_char(t_token *token_head, char *line, int *i)
{
	if (ft_iswordchar(line[*i]))
		token_head = while_sequence(token_head, line, ft_iswordchar, &i);
	if (ft_isspace(line[*i]))
		i++;
		//token_head = while_sequence(token_head, line, ft_isspace, &i);
	if (line[*i] == '\'')
		token_head = find_field(token_head, line, ft_isquote, &i);
	if (line[*i] == '\"')
		token_head = find_field(token_head, line, ft_isdblquote, &i);
	if (line[*i] == '>')
		token_head = find_redir(token_head, line, '>', &i);
	if (line[*i] == '<')
		token_head = find_redir(token_head, line, '<', &i);
	if (line[*i] == '|')
	{
		token_head = token_create(token_head, &(line[*i]), 1, 9);
		(*i)++;
	}
	return (token_head);
}

t_token	*lexer(char *line)
{
	int		i;
	t_token *token_head;

	i = 0;
	token_head = (t_token *)malloc(sizeof(t_token));
	//if !token_head
	token_head = token_head_init(token_head);
	while (line[i] != '\0')
		token_head = check_char(token_head, line, &i);
	print_token(token_head);
	return(token_head);
}