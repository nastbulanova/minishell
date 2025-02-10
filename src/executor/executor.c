/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:08:00 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:15:26 by joaomigu         ###   ########.fr       */
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

static bool	cmd_valid(t_minishell *data, t_exec_data *cmd, char **end_str)
{
	struct stat	st;
	bool		has_slash;

	has_slash = ft_strchr(cmd->cmd, '/') != NULL;
	if ((!has_slash) || (access(cmd->cmd, F_OK) == -1))
	{
		data->exit_code = 127;
		if (!has_slash)
			*end_str = get_err_str(cmd->cmd, "command not found",
					false);
		else if (access(cmd->cmd, F_OK) == -1)
			*end_str = get_err_str(cmd->cmd,
					"No such file or directory", false);
		return (false);
	}
	if (stat(cmd->cmd, &st) == 0)
	{
		data->exit_code = 126;
		if (S_ISDIR(st.st_mode))
			*end_str = get_err_str(cmd->cmd, "Is a directory", false);
		else if (access(cmd->cmd, X_OK) == -1)
			*end_str = get_err_str(cmd->cmd, strerror(errno), true);
		return (false);
	}
	return (true);
}

bool	command_is_valid(t_exec_data *cmd, t_minishell *data)
{
	char	*error;
	char	*final_string;
	bool	result;

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

void	execute_pipe(t_minishell *data, t_exec_data *head, char **envp)
{
	t_exec_data	*current;
	t_exec_data	*previous;
	t_pid_list	*pid_list;
	pid_t		pid;

	current = head;
	pid_list = NULL;
	previous = NULL;
	while (current)
	{
		if (current->next)
			safe_pipe(current->outpipe);
		pid = fork();
		if (pid < 0)
			break ;
		if (pid == 0)
			handle_child(current, previous, envp, head);
		else
			handle_parent(current, previous, &pid_list, pid);
		close_command_fds(previous);
		previous = current;
		current = current->next;
	}
	handle_exit_status(data, pid_list);
}

void	execute_command_list(t_minishell *data, t_exec_data *head, char **envp)
{
	t_exec_data	*current;

	current = head;
	while (current)
	{
		handle_heredoc_redirection(data, current);
		if (data->exit_code == 130)
			break ;
		handle_io_redirections(current);
		current = current->next;
	}
	if (data->exit_code == 130)
		return ;
	if (!head->next)
		execute_non_pipe(data, head, envp);
	else
		execute_pipe(data, head, envp);
	free_array(envp, NULL);
}
