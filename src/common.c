/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:55:01 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 12:55:02 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_minishell	*get_shell(bool init)
{
	static t_minishell	data;

	if (init)
	{
		data.env = NULL;
		data.exec_data = NULL;
		data.exit_code = 0;
		data.token_head = NULL;
		data.prompt = NULL;
		data.heredoc_pipe[0] = -1;
		data.heredoc_pipe[1] = -1;
	}
	return (&data);
}

void	free_array(char **arr, char *temp)
{
	int	i;

	i = -1;
	if (temp)
		free(temp);
	if (!arr || !*arr)
		return ;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

int	c_strcmp(char *str_one, char *str_two)
{
	if (!str_one && !str_two)
		return (1);
	if (!str_one || !str_two)
	{
		if (str_one)
			return (1);
		if (str_two)
			return (-1);
	}
	return (ft_strncmp(str_one, str_two, SIZE_MAX));
}
