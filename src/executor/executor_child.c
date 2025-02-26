/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:17:59 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/26 18:43:10 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @file executor_child.c
 * @brief Handles child process execution in the Minishell project.
 */

/**
 * @brief Closes all file descriptors in the execution chain.
 * 
 * Iterates through the linked list of execution data and closes any open
 * input, output, and pipe file descriptors.
 * 
 * @param temp Pointer to the first node of the execution data linked list.
 */
void	clear_fds(t_exec_data *temp)
{
	while (temp)
	{
		if (temp->input_fd >= 0)
			close_fd(&temp->input_fd);
		if (temp->output_fd >= 0)
			close_fd(&temp->output_fd);
		if (temp->outpipe[0] >= 0)
			close_fd(&temp->outpipe[0]);
		if (temp->outpipe[1] >= 0)
			close_fd(&temp->outpipe[1]);
		temp = temp->next;
	}
}

/**
 * @brief Handles cleanup and process tracking for the parent process.
 * 
 * Closes necessary file descriptors after forking a child process and adds
 * the child's PID to the tracking list.
 * 
 * @param cmd Pointer to the current command execution node.
 * @param previous Pointer to the previous command execution node (if any).
 * @param pid_list Pointer to the PID tracking list.
 * @param pid Process ID of the newly created child process.
 */
void	handle_parent(t_exec_data *cmd, t_exec_data *previous,
		t_pid_list **pid_list, pid_t pid)
{
	add_pid(pid_list, pid);
	if (cmd->outpipe[1] >= 0)
		close_fd(&cmd->outpipe[1]);
	if (previous && previous->outpipe[0] >= 0)
		close_fd(&previous->outpipe[0]);
	if (cmd->input_fd >= 0)
		close_fd(&cmd->input_fd);
	if (cmd->output_fd >= 0)
		close_fd(&cmd->output_fd);
}

/**
 * @brief Sets up input redirections for the child process.
 * 
 * Redirects input from a file descriptor or a pipe from the previous command.
 * If the command is a builtin, the input redirection is skipped.
 * 
 * @param cmd Pointer to the current command execution node.
 * @param previous Pointer to the previous command execution node (if any).
 */
static void	handle_child_input(t_exec_data *cmd, t_exec_data *previous)
{
	if (cmd->input_fd >= 0)
	{
		if (!cmd->is_builtin)
			safe_dup_two(cmd->input_fd, STDIN_FILENO);
		close_fd(&cmd->input_fd);
	}
	else if (previous)
	{
		if (previous->outpipe[0] >= 0)
		{
			safe_dup_two(previous->outpipe[0], STDIN_FILENO);
			close_fd(&previous->outpipe[0]);
		}
	}
}

/**
 * @brief Sets up output redirections for the child process.
 * 
 * Redirects output to a file descriptor or to a pipe for the next command.
 * 
 * @param cmd Pointer to the current command execution node.
 */
static void	handle_child_output(t_exec_data *cmd)
{
	if (cmd->output_fd >= 0)
	{
		safe_dup_two(cmd->output_fd, STDOUT_FILENO);
		close_fd(&cmd->output_fd);
	}
	else if (cmd->next)
	{
		if (cmd->outpipe[1] >= 0)
		{
			safe_dup_two(cmd->outpipe[1], STDOUT_FILENO);
			close_fd(&cmd->outpipe[1]);
		}
	}
}

/**
 * @brief Executes a command in the child process.
 * 
 * Handles input/output redirections, executes builtins directly,
 * or calls `execve` for external commands. If a command is invalid,
 * the child process exits with an error code.
 * 
 * @param cmd Pointer to the current command execution node.
 * @param previous Pointer to the previous command execution node (if any).
 * @param envp Environment variables.
 * @param head Pointer to the head of the execution data linked list.
 */
void	handle_child(t_exec_data *cmd, t_exec_data *previous,
		t_exec_data *head)
{
	int			exit_code;
	t_minishell	*data;

	data = get_shell(false);
	exit_code = 0;
	handle_child_input(cmd, previous);
	handle_child_output(cmd);
	if (previous)
		close_fd(&previous->outpipe[1]);
	if (cmd->is_builtin)
	{
		if (command_is_valid(cmd, data))
			exit_code = execute_builtin(cmd, -1, -1);
		data->exit_code = exit_code;
		minishell_exit(NULL, exit_code, STDERR_FILENO, false);
	}
	else
	{
		if (cmd->next)
			close_fd(&cmd->outpipe[0]);
		if (command_is_valid(cmd, data))
			execute_execve(cmd, data, head);
		else
			minishell_exit(NULL, data->exit_code, STDERR_FILENO, true);
	}
}
