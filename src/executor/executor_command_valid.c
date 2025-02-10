/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_command_valid.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:08:00 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 16:49:57 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	print_and_cleanup_error(t_exec_data *cmd, char *final_string)
{
	ft_putendl_fd(final_string, STDERR_FILENO);
	free(final_string);
	close_fd(&cmd->input_fd);
	close_fd(&cmd->output_fd);
}

static bool cmd_valid_aux(t_minishell *data, t_exec_data *cmd, char **end_str)
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

static bool	cmd_valid(t_minishell *data, t_exec_data *cmd, char **end_str)
{
	bool		has_slash;

	has_slash = ft_strchr(cmd->cmd, '/') != NULL;
	if ((!has_slash) || (access(cmd->cmd, F_OK) == -1))
	{
		data->exit_code = 127;
		if (!has_slash)
			*end_str = get_err_str(cmd->cmd, "command not found", false);
		else if (access(cmd->cmd, F_OK) == -1)
			*end_str = get_err_str(cmd->cmd, "No such file or directory", false);
		return (false);
	}
	else
		return(cmd_valid_aux(data, cmd, end_str));
	return (true);
}

bool	command_is_valid(t_exec_data *cmd, t_minishell *data)
{
	char	*error;
	char	*final_string;
	bool	result;

	final_string = NULL;
	result = true;
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

