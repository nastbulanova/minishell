/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:22:53 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:23:14 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	error_string_aux(char *str, char *final_string, size_t *index_final,
		size_t index)
{
	size_t	str_size;

	str_size = ft_strlen(str);
	while (index < str_size)
	{
		final_string[*index_final] = str[index];
		index++;
		(*index_final)++;
	}
}

char	*get_err_str(char *filename, char *error_str, bool newline)
{
	size_t	final_length;
	char	*final_string;
	char	*template;
	size_t	index;

	template = "minishell: ";
	index = 0;
	index = 0;
	final_length = 0;
	if (newline)
		final_length = (ft_strlen(template) + ft_strlen(filename)
				+ ft_strlen(error_str) + 4);
	else
		final_length = (ft_strlen(template) + ft_strlen(filename)
				+ ft_strlen(error_str) + 3);
	final_string = safe_malloc(final_length);
	error_string_aux(template, final_string, &index, index);
	error_string_aux(filename, final_string, &index, 0);
	final_string[index++] = ':';
	final_string[index++] = ' ';
	error_string_aux(error_str, final_string, &index, 0);
	if (newline)
		final_string[index++] = '\n';
	final_string[index] = '\0';
	return (final_string);
}

void	close_command_fds(t_exec_data *cmd)
{
	if (!cmd)
		return ;
	close_pipe(cmd->outpipe);
	if (cmd->input_fd >= 0)
		close_fd(&cmd->input_fd);
	if (cmd->output_fd >= 0)
		close_fd(&cmd->output_fd);
}

int	execute_builtin(t_exec_data *cmd)
{
	int	exit_code;

	exit_code = 0;
	if (c_strcmp(cmd->cmd, "echo") == 0)
		exit_code = cmd_echo(cmd->opt);
	else if (c_strcmp(cmd->cmd, "cd") == 0)
		exit_code = cmd_cd(cmd->opt);
	else if (c_strcmp(cmd->cmd, "unset") == 0)
		exit_code = cmd_unset(cmd->opt);
	else if (c_strcmp(cmd->cmd, "export") == 0)
		exit_code = cmd_export(cmd->opt);
	else if (c_strcmp(cmd->cmd, "exit") == 0)
		exit_code = cmd_exit(cmd->opt);
	else if (c_strcmp(cmd->cmd, "env") == 0)
		exit_code = cmd_env(cmd->opt);
	else if (c_strcmp(cmd->cmd, "pwd") == 0)
		exit_code = cmd_pwd(cmd->output_fd);
	else
	{
		minishell_exit("Critical error processing built in.", 2, STDERR_FILENO,
			false);
		exit_code = 2;
	}
	return (exit_code);
}
