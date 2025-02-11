/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_common.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:17:42 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/11 10:39:06 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Checks if the redirection list contains a heredoc.
 *
 * This function iterates through the given redirection list and determines
 * if there is a heredoc (`<<`) or quoted heredoc (`<<EOF`).
 *
 * @param redir Pointer to the redirection list.
 * @return true if a heredoc is present, false otherwise.
 */
bool	has_heredoc(t_redir *redir)
{
	if (!redir)
		return (false);
	while (redir)
	{
		if (redir->type == HEREDOC || redir->type == HEREDOC_QUOTED)
			return (true);
		redir = redir->next;
	}
	return (false);
}

/**
 * @brief Checks if the redirection list contains any input redirection.
 *
 * This function iterates through the given redirection list and determines
 * if there is a standard input redirection (`<`) or a heredoc (`<<`).
 *
 * @param redir Pointer to the redirection list.
 * @return true if an input redirection is present, false otherwise.
 */
bool	has_input(t_redir *redir)
{
	if (!redir)
		return (false);
	while (redir)
	{
		if (redir->type == INPUT || redir->type == HEREDOC
			|| redir->type == HEREDOC_QUOTED)
			return (true);
		redir = redir->next;
	}
	return (false);
}

/**
 * @brief Checks if the redirection list contains any output redirection.
 *
 * This function iterates through the given redirection list and determines
 * if there is a standard output redirection (`>`) or an append output (`>>`).
 *
 * @param redir Pointer to the redirection list.
 * @return true if an output redirection is present, false otherwise.
 */
bool	has_output(t_redir *redir)
{
	if (!redir)
		return (false);
	while (redir)
	{
		if (redir->type == OUTPUT || redir->type == OUTPUT_APPEND)
			return (true);
		redir = redir->next;
	}
	return (false);
}

/**
 * @brief Retrieves the first redirection error message, if any.
 *
 * This function iterates through the given redirection list and returns
 * the first encountered error message.
 *
 * @param redir Pointer to the redirection list.
 * @return Pointer to the error message string, or NULL if no error is found.
 */
char	*get_rdir_error(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir)
	{
		if (redir->error)
			return (redir->error);
		redir = redir->next;
	}
	return (NULL);
}

/**
 * @brief Initializes an execution data structure.
 *
 * This function sets default values for an execution data structure,
 * ensuring that all members are properly initialized before use.
 *
 * @param exec_data Pointer to the execution data structure to initialize.
 */
void	init_cmd(t_exec_data *exec_data)
{
	exec_data->cmd = NULL;
	exec_data->opt = NULL;
	exec_data->is_builtin = false;
	exec_data->redirs = NULL;
	exec_data->exit_status = 0;
	exec_data->input_fd = -1;
	exec_data->output_fd = -1;
	exec_data->outpipe[0] = -1;
	exec_data->outpipe[1] = -1;
}
