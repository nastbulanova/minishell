/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:18:15 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:22:31 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_pid_list(t_pid_list **head)
{
	t_pid_list	*current;
	t_pid_list	*next;

	current = *head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

t_pid_list	*create_pid_node(pid_t pid)
{
	t_pid_list	*new_node;

	new_node = safe_malloc(sizeof(t_pid_list));
	new_node->pid = pid;
	new_node->next = NULL;
	return (new_node);
}

void	add_pid(t_pid_list **head, pid_t pid)
{
	t_pid_list	*new_node;
	t_pid_list	*current;

	new_node = create_pid_node(pid);
	if (!new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

static void	exit_status_aux(t_minishell *data, t_exec_data *head)
{
	int	signal;
	int	status;

	if (head->exit_status != 0)
		data->exit_code = head->exit_status;
	else
	{
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			signal = WTERMSIG(status);
			data->exit_code = 128 + signal;
		}
		else
			data->exit_code = 1;
	}
}

void	handle_exit_status(t_minishell *data, t_pid_list *pid_list)
{
	int			status;
	int			signal;
	t_pid_list	*current;
	t_exec_data	*head;

	head = data->list_exec_data;
	current = pid_list;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		exit_status_aux(data, head);
		head = head->next;
		current = current->next;
	}
	free_pid_list(&pid_list);
}
