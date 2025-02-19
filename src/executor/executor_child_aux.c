/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:18:15 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/19 12:06:10 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @file executor_child_aux.c
 * @brief Auxiliary functions for managing child processes in Minishell.
 */

/**
 * @brief Frees the memory allocated for a list of process IDs.
 * 
 * @param head Pointer to the head of the pid list.
 */
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

/**
 * @brief Creates a new node for storing a process ID.
 * 
 * @param pid The process ID to store.
 * @return Pointer to the newly created node.
 */
t_pid_list	*create_pid_node(pid_t pid)
{
	t_pid_list	*new_node;

	new_node = safe_malloc(sizeof(t_pid_list));
	new_node->pid = pid;
	new_node->next = NULL;
	return (new_node);
}

/**
 * @brief Adds a new process ID node to the end of the pid list.
 * 
 * @param head Pointer to the head of the pid list.
 * @param pid The process ID to add.
 */
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

/**
 * @brief Determines and updates the exit status of the shell.
 * 
 * @param data Pointer to the Minishell structure.
 * @param head Pointer to the execution data list.
 * @param status The status returned by waitpid.
 */
static void	exit_status_aux(t_minishell *data, t_exec_data *head, int status)
{
	int	signal;

	signal = 0;
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

/**
 * @brief Handles the exit statuses of all child processes.
 * 
 * Waits for all child processes in the pid list to finish and updates the
 * shell's exit status accordingly.
 * 
 * @param data Pointer to the Minishell structure.
 * @param pid_list Pointer to the list of process IDs.
 */
void	handle_exit_status(t_minishell *data, t_pid_list *pid_list)
{
	int			status;
	t_pid_list	*current;
	t_exec_data	*head;

	status = 0;
	head = data->list_exec_data;
	current = pid_list;
	while (current)
	{
		waitpid(current->pid, &status, 0);
		exit_status_aux(data, head, status);
		head = head->next;
		current = current->next;
	}
	free_pid_list(&pid_list);
}
