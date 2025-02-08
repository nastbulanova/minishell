# include "../inc/minishell.h"

void print_array(char **arr)
{
    int i;
    
    i = -1;
    while (arr[++i])
        ft_printf("'%s'\n", arr[i]);
}

void	print_exec_data(t_minishell *data)
{
	t_exec_data	*tmp;
	t_redir		*redirs;
	char	**list;
	int i;
	int j;

	i = 0;
	tmp = data->list_exec_data;
	while (tmp)
	{
		printf("\n*** %d ***\n", i);
		printf("cmd: %s\n", tmp->cmd);
		printf("builtin: %d\n", tmp->is_builtin);
		printf("opt: ");
		j = 0;
		list = tmp->opt;
		if (list)
		{
			while (list[j])
			{
				printf("%s ", list[j]);
				j++;
			}
		}
		printf("\n");
		printf("redirs:\n");
		redirs = tmp->redirs;
		while (redirs)
		{
			printf("%d ", redirs->type);
			if (redirs->str)
				printf("%s", redirs->str);
			printf("\n");
			redirs = redirs->next;
		}
		tmp = tmp->next;
		i++;
	}
	printf("*** all printed ***\n");
}
