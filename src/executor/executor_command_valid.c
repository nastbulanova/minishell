/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command_valid.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:08:00 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/03 14:03:50 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Prints an error message and cleans up resources.
 *
 * This function outputs an error message, frees the allocated error string,
 * and closes the input and output file descriptors of the given command.
 *
 * @param cmd The command execution data containing file descriptors.
 * @param final_string The formatted error message to print and free.
 */
static void	print_and_cleanup_error(t_exec_data *cmd, char *final_string)
{
	ft_putendl_fd(final_string, STDERR_FILENO);
	free(final_string);
	close_fd(&cmd->input_fd);
	close_fd(&cmd->output_fd);
}

/**
 * @brief Auxiliary function to check if a command is valid.
 *
 * This function verifies if the given command is a directory or if it lacks
 * execution permissions, updating the exit code and error message accordingly.
 *
 * @param data The minishell data structure containing the exit code.
 * @param cmd The command execution data to validate.
 * @param end_str Pointer to store the generated error message if invalid.
 * @return true if the command is valid, false otherwise.
 */
static bool	cmd_valid_aux(t_minishell *data, t_exec_data *cmd, char **end_str)
{
	struct stat	st;

	if (stat(cmd->cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		data->exit_code = 126;
		*end_str = get_err_str(cmd->cmd, "Is a directory", false);
		return (false);
	}
	if (access(cmd->cmd, X_OK) == -1)
	{
		data->exit_code = 126;
		*end_str = get_err_str(cmd->cmd, strerror(errno), true);
		return (false);
	}
	return (true);
}

/**
 * @brief Checks if the given command exists and is executable.
 *
 * This function determines if the command is valid by checking its existence
 * and execution permissions. It handles cases where the command is missing,
 * is not found in PATH, or lacks execution rights.
 *
 * @param data The minishell data structure containing the exit code.
 * @param cmd The command execution data to validate.
 * @param end_str Pointer to store the generated error message if invalid.
 * @return true if the command is valid, false otherwise.
 */
static bool	cmd_valid(t_minishell *data, t_exec_data *cmd, char **end_str)
{
	bool		has_slash;
	struct stat	statbuf;

	has_slash = ft_strchr(cmd->cmd, '/') != NULL;
	if ((!has_slash) || (access(cmd->cmd, F_OK) == -1))
	{
		data->exit_code = 127;
		if (!has_slash)
			*end_str = get_err_str(cmd->cmd, "command not found", false);
		else if (access(cmd->cmd, F_OK) == -1)
		{
			if (stat(cmd->cmd, &statbuf) != 0)
				return (*end_str = get_err_str(cmd->cmd,
						"No such file or directory", false), false);
			if (S_ISDIR(statbuf.st_mode))
				*end_str = get_err_str(cmd->cmd, "Is a directory", false);
			else
				*end_str = get_err_str(cmd->cmd,
						"No such file or directory", false);
		}
		return (false);
	}
	else
		return (cmd_valid_aux(data, cmd, end_str));
	return (true);
}

/**
 * @brief Determines if a command is valid and executable.
 *
 * This function checks whether a command is built-in or external, verifies
 * its validity, and handles redirection errors if present.
 *
 * @param cmd The command execution data.
 * @param data The minishell data structure containing the exit code.
 * @return true if the command is valid and executable, false otherwise.
 */
bool	command_is_valid(t_exec_data *cmd, t_minishell *data)
{
	char	*error;
	char	*final_string;
	bool	result;

	final_string = NULL;
	result = true;
	if (!cmd->cmd)
		return (false);
	if (cmd->exit_status != 0)
	{
		data->exit_code = cmd->exit_status;
		error = get_rdir_error(cmd->redirs);
		final_string = ft_strdup(error);
		result = false;
	}
	else if (!cmd->is_builtin)
		result = cmd_valid(data, cmd, &final_string);
	if (!result)
		print_and_cleanup_error(cmd, final_string);
	return (result);
}
