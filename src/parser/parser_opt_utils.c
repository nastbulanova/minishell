#include "../../inc/minishell.h"

t_opt_llist	*opt_create(char *opt)
{
	t_opt_llist	*tmp;

	tmp = (t_opt_llist *)malloc(sizeof(t_opt_llist));
	if (!tmp)
		return (NULL);
	tmp->opt = opt;
	tmp->next = NULL;
	return (tmp);
}


t_parser_error	opt_add(t_minishell **data, char *opt)
{
	t_opt_llist	*new;
	t_opt_llist	*current;

	if (!opt)
		return(MALLOC_ERROR);
	if (*opt == '\0')
		return(free(opt), OK);
	new = opt_create(opt);
	if (!(*data)->exec_data->opt_llist)
		(*data)->exec_data->opt_llist = new;
	else
	{
		current = (*data)->exec_data->opt_llist;
        while (current->next)
            current = current->next;
		current->next = new;
	}
	return (OK);
}

char	*opt_check(t_minishell **data, t_token ***token)
{
	char	*opt;

	opt = NULL;
	/*if ((**token)->type == 0)
		opt = ft_itoa((*data)->exit_code);	
	else if ((**token)->type == 2)
	{
		tmp = ft_substr((**token)->start, 0, (**token)->len);
		opt = env_var_replace(*data, tmp);
	}
	else*/ if ((**token)->type == FIELD)
		opt = ft_substr((**token)->start, 0, (**token)->len);
	else
		opt = open_field(*data, **token);
	return(opt);
}

