/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:54:23 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/17 12:12:25 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	dirty_check(t_token *input)
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

static void	print_redirs(t_exec_data *tmp)
{
	t_redir	*redirs;

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
}

void	print_exec_data(t_minishell *data)
{
	t_exec_data	*tmp;
	char		**list;
	int			i;
	int			j;

	i = 0;
	tmp = data->list_exec_data;
	while (tmp)
	{
		printf("\n*** %d ***\ncmd: %s\nbuiltin: %d\n", i, tmp->cmd,
			tmp->is_builtin);
		printf("opt: ");
		j = -1;
		list = tmp->opt;
		if (list)
		{
			while (list[++j])
				printf("%s ", list[j]);
		}
		print_redirs(tmp);
		tmp = tmp->next;
		i++;
	}
	printf("*** all printed ***\n");
}
