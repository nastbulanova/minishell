/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_isolated.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:16:38 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/26 15:11:48 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * @brief Executes a command using execve.
 *
 * This function replaces the current process image with a new process image
 * specified by the command structure. If execve fails, it handles the error,
 * sets the appropriate exit code, clears file descriptors, and exits the shell.
 *
 * @param cmd Pointer to the command structure containing the command and 
 * options.
 * @param envp Environment variables array.
 * @param head Pointer to the head of the execution data list (used for cleanup).
 */
void	execute_execve(t_exec_data *cmd, t_minishell *data, t_exec_data *head)
{
	int	exit_code;

	set_state_signal_handlers(CHILD);
	if (execve(cmd->cmd, cmd->opt, env_to_array(data->env)) < 0)
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

/**
 * @brief Executes an isolated command (non-piped) in a separate process.
 *
 * If the command is a builtin, it is executed directly. Otherwise, 
 * a child process
 * is created using fork(), and execve is called in the child process.
 * The function also manages signal handling and process exit status.
 *
 * @param data Pointer to the minishell structure containing shell state.
 * @param cmd Pointer to the command structure.
 * @param envp Environment variables array.
 */
static void	execute_isolated_aux(t_minishell *data, t_exec_data *cmd,
		int stdin_backup, int stdout_backup)
{
	pid_t		pid;
	t_pid_list	*pid_list;

	pid_list = NULL;
	if (cmd->is_builtin)
	{
		update_last_command(data->env, cmd->cmd);
		data->exit_code = execute_builtin(cmd, stdin_backup, stdout_backup);
	}
	else
	{
		set_state_signal_handlers(IGNORE);
		update_last_command(data->env, cmd->cmd);
		pid = fork();
		if (pid < 0)
			return ;
		if (pid == 0)
			execute_execve(cmd, data, NULL);
		else
		{
			add_pid(&pid_list, pid);
			handle_exit_status(data, pid_list);
			set_state_signal_handlers(MAIN);
		}
	}
}

/**
 * @brief Executes a non-piped command with input/output redirections.
 *
 * This function checks if the command is valid, handles input/output 
 * redirections,
 * and executes the command in an isolated process.
 *
 * @param data Pointer to the minishell structure containing shell state.
 * @param cmd Pointer to the command structure.
 * @param envp Environment variables array.
 */
void	execute_non_pipe(t_minishell *data, t_exec_data *cmd)
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
		execute_isolated_aux(data, cmd, stdin_backup, stdout_backup);
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close_fd(&stdin_backup);
		close_fd(&stdout_backup);
	}
}
