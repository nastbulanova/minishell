#include "minishell.h"

t_token	*token_create(char *start, int len, int type)
{
	t_token	*tmp;

	tmp = NULL;
	tmp = (t_token *)malloc(sizeof(t_token));
	if(!tmp)
		return (NULL);
	if (len == 0)
	{
		start = ft_strdup("");
		if (!start)
			return (NULL);
	}
	tmp->start = ft_substr(start, 0, len);
	if (!tmp->start)
		return(NULL);
	tmp->len = len;
	tmp->type = type;
	tmp->next = NULL;
	tmp->prev = NULL;
	return(tmp);
}

t_parser_error token_add(t_token ***token_head, char *start, int len, t_token_type type)
{
	t_token	*new;
	t_token	*current;

	new = NULL;
	new = token_create(start, len, type);
	if (!new)
		return (MALLOC_ERROR);
	if (!(**token_head))
		**token_head = new;
	else
	{
		current = **token_head;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (OK);
}
