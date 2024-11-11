#include "minishell.h"

int	opt_count(t_token *token)
{
	t_token	*tmp;
	int		count;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (!(tmp->type >= 1 && tmp->type <= 4))
			break ;
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	opt_check(t_minishell **data, t_token **token)
{
	t_token	*tmp;
	int		count;
	int		i;

	tmp = (*token);
	count = opt_count(tmp);
	(*data)->exec_data->opt = (char **)malloc((count + 1) * sizeof(char *));
	//if (!data->exec_data->opt)
	///////////////////////////////////////////////////////////////////////	error
	i = 0;
	while (i < count)
	{
		if (tmp->type == 1)
			(*data)->exec_data->opt[i] = ft_substr(tmp->start, 0, tmp->len);
		else if (tmp->type == 2)
			(*data)->exec_data->opt[i] = env_var_replace(*data, ft_substr(tmp->start, 0, tmp->len));
		else if (tmp->type == 3)
			(*data)->exec_data->opt[i] = ft_substr(tmp->start, 0, tmp->len);
		else
			(*data)->exec_data->opt[i] = open_field(*data, *token);
		tmp = tmp->next;// check exist of tmp->next
        printf("opt %d %s\n", i, (*data)->exec_data->opt[i]);//////////////////////////to delete
		i++;
	}
    (*data)->exec_data->opt[i] = NULL;
    (*token) = tmp->prev;
}
