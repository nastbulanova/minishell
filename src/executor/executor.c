/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:08:00 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/24 13:52:03 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * @file executor.c
 * @brief Executes commands and handles piping in the minishell project.
 */

static void	execute_pipe_aux(t_pid_list	**pid_list, t_exec_data *current,
		t_exec_data *previous, t_exec_data *head)
{
	pid_t		pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		free_pid_list(pid_list);
		handle_child(current, previous, head);
	}
	else
		handle_parent(current, previous, pid_list, pid);
	close_command_fds(previous);
}

/**
 * @brief Executes a sequence of piped commands.
 *
 * This function iterates through the list of commands, creating pipes where
 *  needed,
 * forking child processes to execute commands, and managing parent processes.
 *
 * @param data The minishell state structure.
 * @param head Pointer to the first command in the execution list.
 * @param envp The environment variables array.
 */
void	execute_pipe(t_minishell *data, t_exec_data *head)
{
	t_exec_data	*current;
	t_exec_data	*previous;
	t_pid_list	*pid_list;

	current = head;
	pid_list = NULL;
	previous = NULL;
	while (current)
	{
		if (current->next)
			safe_pipe(current->outpipe);
		if (!previous)
			update_last_command(data->env, current->cmd);
		execute_pipe_aux(&pid_list, current, previous, head);
		previous = current;
		current = current->next;
	}
	handle_exit_status(data, pid_list);
}

/**
 * @brief Executes a list of commands, handling redirections and pipelines.
 *
 * This function processes each command for heredoc and IO redirections 
 * before execution.
 * It determines whether to execute a single command or a pipeline of commands.
 *
 * @param data The minishell state structure.
 * @param head Pointer to the first command in the execution list.
 * @param envp The environment variables array.
 */
void	execute_command_list(t_minishell *data, t_exec_data *head)
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
		execute_non_pipe(data, head);
	else
		execute_pipe(data, head);
}
