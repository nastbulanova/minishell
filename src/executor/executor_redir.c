/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:15:59 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/01 11:08:01 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * @brief Handles output redirection by opening the specified file.
 *
 * This function closes the provided output file descriptor (if any) and opens
 * the file specified in the redirection structure. The file is opened with
 * either truncation or append mode, depending on the redirection type.
 * If an error occurs, it sets the appropriate error message and exit status.
 *
 * @param cmd The execution data containing exit status.
 * @param current The redirection structure specifying the file and type.
 * @param temp_output_fd Pointer to the temporary output file descriptor.
 */
static void	process_io_output(t_exec_data *cmd, t_redir *current,
		int *temp_output_fd)
{
	int	flags;

	close_fd(temp_output_fd);
	if (current->type == OUTPUT)
		flags = (O_WRONLY | O_CREAT | O_TRUNC);
	else
		flags = (O_WRONLY | O_CREAT | O_APPEND);
	*temp_output_fd = open(current->str, flags, 0644);
	if (*temp_output_fd < 0)
	{
		cmd->exit_status = 1;
		if (errno == ENOENT)
			current->error = get_err_str(current->str,
					"No such file or directory", false);
		else if (errno == EACCES)
		{
			cmd->exit_status = 1;
			current->error = get_err_str(current->str,
					"Permission denied", false);
		}
		else
			current->error = get_err_str(current->str, "Unknown error", false);
	}
}

/**
 * @brief Handles input redirection by opening the specified file.
 *
 * This function closes the provided input file descriptor (if any) and opens
 * the file specified in the redirection structure for reading. If an error
 * occurs, it sets the appropriate error message and exit status.
 *
 * @param cmd The execution data containing exit status.
 * @param current The redirection structure specifying the file.
 * @param temp_input_fd Pointer to the temporary input file descriptor.
 */
static void	process_io_input(t_exec_data *cmd, t_redir *current,
		int *temp_input_fd)
{
	close_fd(temp_input_fd);
	*temp_input_fd = open(current->str, O_RDONLY);
	if (*temp_input_fd < 0)
	{
		cmd->exit_status = 1;
		if (errno == ENOENT)
			current->error = get_err_str(current->str,
					"No such file or directory", false);
		else if (errno == EACCES)
			current->error = get_err_str(current->str,
					"Permission denied", false);
		else
			current->error = get_err_str(current->str, "Unknown error", false);
	}
}

/**
 * @brief Finalizes the redirection process by setting file descriptors.
 *
 * If no error occurred during redirection processing, this function assigns
 * the temporary input and output file descriptors to the execution structure.
 * If an error occurred, it closes any opened file descriptors.
 *
 * @param cmd The execution data where final descriptors will be stored.
 * @param error_msg The error message (if any) from redirection processing.
 * @param temp_input_fd Pointer to the temporary input file descriptor.
 * @param temp_output_fd Pointer to the temporary output file descriptor.
 */
static void	finalize_redirections(t_exec_data *cmd, char *error_msg,
		int *temp_input_fd, int *temp_output_fd)
{
	if (!error_msg)
	{
		if (*temp_input_fd >= 0)
		{
			if (cmd->input_fd >= 0)
				close_fd(&cmd->input_fd);
			cmd->input_fd = *temp_input_fd;
		}
		cmd->output_fd = *temp_output_fd;
	}
	else
	{
		close_fd(temp_input_fd);
		close_fd(temp_output_fd);
	}
}

/**
 * @brief Processes input and output redirections for a command.
 *
 * Iterates through the command's redirection list, handling input, output,
 * and append redirections. If an error occurs, the process is stopped.
 *
 * @param cmd The execution data containing redirection details.
 */
void	handle_io_redirections(t_exec_data *cmd)
{
	t_redir	*current;
	int		temp_input_fd;
	int		temp_output_fd;
	char	*error_msg;

	error_msg = NULL;
	temp_input_fd = -1;
	temp_output_fd = -1;
	current = cmd->redirs;
	while (current && !error_msg)
	{
		if (current->type == AMBIGUOUS)
		{
			current->error = get_err_str(current->str, "ambiguous redirect",
					false);
			cmd->exit_status = 1;
		}
		if (current->type == INPUT)
			process_io_input(cmd, current, &temp_input_fd);
		else if (current->type == OUTPUT || current->type == OUTPUT_APPEND)
			process_io_output(cmd, current, &temp_output_fd);
		error_msg = current->error;
		current = current->next;
	}
	finalize_redirections(cmd, error_msg, &temp_input_fd, &temp_output_fd);
}

/**
 * @brief Handles heredoc redirection for a command.
 *
 * Iterates through the command's redirection list and processes heredoc
 * entries. A pipe is created for heredoc input, and if interrupted,
 * the appropriate cleanup is performed.
 *
 * @param data The minishell structure containing heredoc pipe details.
 * @param head The execution data containing redirections.
 */
void	handle_heredoc_redirection(t_minishell *data, t_exec_data *head)
{
	t_redir	*current;

	current = head->redirs;
	while (current && data->exit_code != 130)
	{
		if (current->type == HEREDOC || current->type == HEREDOC_QUOTED)
		{
			close_pipe(data->heredoc_pipe);
			if (safe_pipe(data->heredoc_pipe))
			{
				heredoc_loop(current, data->heredoc_pipe[1]);
				close_fd(&data->heredoc_pipe[1]);
			}
			if (data->exit_code == 130)
				close_fd(&data->heredoc_pipe[0]);
		}
		current = current->next;
	}
	if (data->heredoc_pipe[0] >= 0)
	{
		head->input_fd = data->heredoc_pipe[0];
		data->heredoc_pipe[0] = -1;
		data->heredoc_pipe[1] = -1;
	}
}
