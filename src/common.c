/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:55:01 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/20 15:02:17 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/**
 * @file common.c
 * @brief Common utility functions for Minishell.
 */

/**
 * @brief Retrieves the singleton instance of the shell data structure.
 *
 * @param init If true, initializes the shell data structure.
 * @return Pointer to the shell instance.
 */
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

/**
 * @brief Frees a dynamically allocated array of strings.
 *
 * @param arr The array to be freed.
 * @param temp An optional temporary string to free.
 */
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
	arr = NULL;
}

/**
 * @brief Compares two strings safely, handling NULL pointers.
 *
 * @param str_one First string to compare.
 * @param str_two Second string to compare.
 * @return 0 if strings are equal, nonzero otherwise.
 */
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
