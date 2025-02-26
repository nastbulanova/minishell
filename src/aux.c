/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:55:21 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/26 15:10:31 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Allocates memory safely and initializes it to zero.
 *
 * This function wraps malloc, ensuring that allocation failures are detected.
 * It initializes the allocated memory to zero and prints an error message
 * if allocation fails.
 *
 * @param bytes The number of bytes to allocate.
 * @return A pointer to the allocated memory, or NULL if allocation fails.
 */
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
	{
		ft_putstr_fd("Malloc failure\n", STDERR_FILENO);
		return (NULL);
	}
	ft_memset(ret, 0, bytes);
	return (ret);
}

/**
 * @brief Prints an error message and terminates the shell.
 *
 * This function retrieves the shell instance, prints an error message
 * including the function name where the error occurred, and then frees
 * allocated resources before exiting with failure status.
 *
 * @param error The error message to display.
 * @param function_name The name of the function where the error occurred.
 */
void	error_exit(const char *error, const char *function_name)
{
	t_minishell	*data;

	data = get_shell(NULL);
	ft_putstr_fd(RB "", STDERR_FILENO);
	ft_putstr_fd((char *)error, STDERR_FILENO);
	ft_putstr_fd(" ", STDERR_FILENO);
	ft_putstr_fd((char *)function_name, STDERR_FILENO);
	ft_putstr_fd("\n" RST, STDERR_FILENO);
	minishell_free(data);
	exit(EXIT_FAILURE);
}

/**
 * @brief Frees allocated memory associated with the shell instance.
 *
 * This function releases memory used by the shell, including the prompt,
 * environment variables, execution data, and execution environment. It also
 * ensures that any open pipes are closed and clears the command history.
 *
 * @param data A pointer to the shell structure to be freed.
 */
void	minishell_free(t_minishell *data)
{
	clear_history();
	if (data)
	{
		if (data->prompt)
			free(data->prompt);
		if (data->env)
			env_free(data->env);
		if (data->list_exec_data)
			free_parser_data(&data);
		if (data->exec_env)
			free_array(data->exec_env, NULL);
		close_pipe(data->heredoc_pipe);
	}
}

bool	is_string_empty(char *input)
{
	size_t	idx;

	idx = 0;
	while (input[idx])
	{
		if (!ft_iswhitespace(input[idx]))
			return (false);
		idx++;
	}
	return (true);
}
