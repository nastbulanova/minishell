#include "../../inc/minishell.h"

int	opt_llist_len(t_opt_llist *opt_llist)
{
	int			count;
	t_opt_llist	*head;

	head = opt_llist;
	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}


char	**opt_llist_to_array(t_opt_llist *opt_llist)
{
	char		**list;
	t_opt_llist	*head;
	int			i;
	int			count;

	count = opt_llist_len(opt_llist);
	list = (char **)malloc(sizeof(char *) * (count + 1));
	if (!list)
		return(NULL);
	head = opt_llist;
	i = 0;
	while (i < count)
	{
		list[i] = ft_strdup(head->opt);
		if (!list[i])
		{
			free_array(list, NULL);
			return(NULL);
		}
		head = head->next;
		i++;
	}
	list[i] = NULL;
	return(opt_llist = NULL, list);
}

t_exec_data	*exec_data_init(void)
{
	t_exec_data *exec_data;

	exec_data = (t_exec_data *)malloc(sizeof(t_exec_data));
	if (!exec_data)
		return(NULL);
	exec_data->cmd = NULL;
	exec_data->opt_llist = NULL;
	exec_data->opt = NULL;
	exec_data->is_builtin = 0;
	exec_data->exit_status = 0;
	exec_data->redirs = NULL;
	exec_data->next = NULL;
	exec_data->input_fd = -1;
	exec_data->output_fd = -1;
	exec_data->outpipe[0] = -1;
	exec_data->outpipe[1] = -1;
	return(exec_data);
}


t_parser_error	exec_data_append(t_minishell **data, int create)
{
	t_exec_data *tmp;

	if ((*data)->exec_data->opt_llist)
	{
		(*data)->exec_data->opt = opt_llist_to_array((*data)->exec_data->opt_llist);
		if(!(*data)->exec_data->opt)
			return(MALLOC_ERROR);
		free_opt_llist(&((*data)->exec_data->opt_llist));
		(*data)->exec_data->opt_llist = NULL;
	}
	if (!(*data)->list_exec_data)
		(*data)->list_exec_data = (*data)->exec_data;
	else
	{
		tmp = (*data)->list_exec_data;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (*data)->exec_data;
		(*data)->exec_data = NULL;
	}
	if (create)
	{
		(*data)->exec_data = exec_data_init();
		if (!(*data)->exec_data)
			return(MALLOC_ERROR);
	}
	return(OK);
}
