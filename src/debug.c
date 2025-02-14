/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:54:23 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/14 15:14:45 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool dirty_check(t_token *input)
{
	if (c_strcmp(input->start, "\"$\"") == 0)
		return (true);
	if (c_strcmp(input->start, "$") == 0)
		return (true);
	return (false);
}
void	print_array(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
		ft_printf("'%s'\n", arr[i]);
}

void	print_exec_data(t_minishell *data)
{
	t_exec_data	*tmp;
	t_redir		*redirs;
	char		**list;
	int			i;
	int			j;

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
