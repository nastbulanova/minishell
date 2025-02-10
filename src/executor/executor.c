/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:08:00 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 16:58:15 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
