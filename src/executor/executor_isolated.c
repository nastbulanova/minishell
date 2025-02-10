/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_isolated.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:16:38 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 16:49:09 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_execve(t_exec_data *cmd, char **envp, t_exec_data *head)
{
	int	exit_code;

	if (execve(cmd->cmd, cmd->opt, envp) < 0)
	{
		if (errno == ENOENT)
			exit_code = 1;
		else if (errno == EACCES)
			exit_code = 1;
		else
			exit_code = 1;
		if (head)
			clear_fds(head);
		minishell_exit(get_err_str(cmd->cmd, strerror(errno), true), exit_code,
			STDERR_FILENO, true);
	}
}

static void	execute_isolated_aux(t_minishell *data, t_exec_data *cmd,
		char **envp)
{
	pid_t		pid;
	t_pid_list	*pid_list;

	pid_list = NULL;
	if (cmd->is_builtin)
		data->exit_code = execute_builtin(cmd);
	else
	{
		set_state_signal_handlers(CHILD);
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
			execute_execve(cmd, envp, NULL);
		else
		{
			set_state_signal_handlers(MAIN);
			add_pid(&pid_list, pid);
			handle_exit_status(data, pid_list);
		}
	}
}

void	execute_non_pipe(t_minishell *data, t_exec_data *cmd, char **envp)
{
	int	stdin_backup;
	int	stdout_backup;

	if (command_is_valid(cmd, data))
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
		if (cmd->input_fd >= 0)
		{
			safe_dup_two(cmd->input_fd, STDIN_FILENO);
			close_fd(&cmd->input_fd);
		}
		if (cmd->output_fd >= 0)
		{
			safe_dup_two(cmd->output_fd, STDOUT_FILENO);
			close_fd(&cmd->output_fd);
		}
		execute_isolated_aux(data, cmd, envp);
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close_fd(&stdin_backup);
		close_fd(&stdout_backup);
	}
}

