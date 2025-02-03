#include "../../inc/minishell.h"

t_redir	*redir_create(char *str, t_token_type type)
{
	t_redir	*tmp;

	tmp = (t_redir *)malloc(sizeof(t_redir));
	if (!tmp)
		return(free(str), NULL);
	tmp->str = str;
	if (type == REDIR_OUT)
		tmp->type = OUTPUT;
	else if (type == REDIR_IN)
		tmp->type = INPUT;
	else if (type == REDIR_APPEND)
		tmp->type = OUTPUT_APPEND;
	else if (type == WORD)
		tmp->type = HEREDOC;
	else
		tmp->type = HEREDOC_QUOTED;
	tmp->error = NULL;
	tmp->next = NULL;
	return(tmp);
}


t_parser_error	redir_add(t_minishell ***data, char *str, int type)
{
	t_redir	*new;
	t_redir	*current;

	if (!str)
		return (MALLOC_ERROR);
	new = redir_create(str, type);
	if (!new)
		return (MALLOC_ERROR);
	if (!(**data)->exec_data->redirs)
		(**data)->exec_data->redirs = new;
	else
	{
		current = (**data)->exec_data->redirs;
        while (current->next)
            current = current->next;
		current->next = new;
	}
	return (OK);
}
t_parser_error	redir_check(t_minishell **data, t_token ***token)
{
	char	*str;
	t_token	**next;

	str = NULL;
	next = NULL;
	if ((**token)->next && (**token)->next->type >= WORD && (**token)->next->type <= EXP_FIELD)
	{
		next = &(**token)->next;
		str = opt_check(data, &next);
		if (!str)
			return(MALLOC_ERROR);
		if (*str == '\0')
		{
			free(str);
			str = ft_substr((*next)->start, 0, (*next)->len);
		}
		if (!str)
			return(MALLOC_ERROR);
	}
	else
		return(SYNTAX_ERROR);
	if (redir_add(&data, str, (**token)->type) == OK)
		return((**token) = (**token)->next, OK);
	else
		return (MALLOC_ERROR);
}


t_parser_error	heredoc_check(t_minishell **data, t_token ***token)
{
	int		type;
	char	*str;
	t_token	**next;

	type = 0;
	str = NULL;
	if ((**token)->next)
	{
		next = &(**token)->next;
		type = (*next)->type;
		if (type == WORD || type == FIELD || type == EXP_FIELD)
			str = ft_substr((*next)->start, 0, (*next)->len);
		else
			return(SYNTAX_ERROR);
		if (!str)
			return(MALLOC_ERROR);
		if (redir_add(&data, str, type) == OK)
			return((**token) = (**token)->next, OK);
		else
			return(MALLOC_ERROR);
	}
	else
		return(SYNTAX_ERROR);
	return(0);
}