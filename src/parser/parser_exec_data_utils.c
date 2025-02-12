/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exec_data_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:51:20 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/12 11:26:50 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Calculates the length of an option linked list.
 *
 * Iterates through the list and returns the number of nodes.
 *
 * @param opt_llist Pointer to the head of the option linked list.
 * @return The number of elements in the list.
 */
int	opt_llist_len(t_opt_llist *opt_llist)
{
	int			count;
	t_opt_llist	*head;

	head = opt_llist;
	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

/**
 * @brief Converts an option linked list to an array.
 *
 * Allocates and fills an array with duplicates of the options.
 *
 * @param opt_llist Pointer to the option linked list.
 * @return Array of strings, or NULL on failure.
 */
char	**opt_llist_to_array(t_opt_llist *opt_llist)
{
	char		**list;
	t_opt_llist	*head;
	int			i;
	int			count;

	count = opt_llist_len(opt_llist);
	list = (char **)malloc(sizeof(char *) * (count + 1));
	if (!list)
		return (NULL);
	head = opt_llist;
	i = 0;
	while (i < count)
	{
		list[i] = ft_strdup(head->opt);
		if (!list[i])
			return (free_array(list, NULL), NULL);
		head = head->next;
		i++;
	}
	list[i] = NULL;
	return (opt_llist = NULL, list);
}

/**
 * @brief Initializes execution data.
 *
 * Allocates and sets default values for a t_exec_data structure.
 *
 * @return Pointer to the initialized execution data, or NULL on failure.
 */
t_exec_data	*exec_data_init(void)
{
	t_exec_data	*exec_data;

	exec_data = (t_exec_data *)malloc(sizeof(t_exec_data));
	if (!exec_data)
		return (NULL);
	exec_data->cmd = NULL;
	exec_data->opt_llist = NULL;
	exec_data->opt = NULL;
	exec_data->is_builtin = 0;
	exec_data->exit_status = 0;
	exec_data->redirs = NULL;
	exec_data->next = NULL;
	exec_data->input_fd = -1;
	exec_data->output_fd = -1;
	exec_data->outpipe[0] = -1;
	exec_data->outpipe[1] = -1;
	return (exec_data);
}

/**
 * @brief Appends execution data to the end of the list.
 *
 * Traverses the list and links the new execution data at the end.
 *
 * @param list_head Pointer to the head of the execution data list.
 * @param exec_data Pointer to the execution data to append.
 */
static void	put_last(t_exec_data **list_head, t_exec_data *exec_data)
{
	t_exec_data	*tmp;

	tmp = *list_head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = exec_data;
}

/**
 * @brief Appends execution data to the minishell structure.
 *
 * Converts the option list to an array, frees it, appends the current execution
 * data to the list, and optionally creates a new execution data node.
 *
 * @param data Double pointer to the minishell data structure.
 * @param create Flag indicating if a new execution data node should be created.
 * @return OK on success, or MALLOC_ERROR on failure.
 */
t_parser_error	exec_data_append(t_minishell **data, int create)
{
	if ((*data)->exec_data->opt_llist)
	{
		(*data)->exec_data->opt = opt_llist_to_array(
				(*data)->exec_data->opt_llist);
		if (!(*data)->exec_data->opt)
			return (MALLOC_ERROR);
		free_opt_llist(&((*data)->exec_data->opt_llist));
		(*data)->exec_data->opt_llist = NULL;
	}
	if (!(*data)->list_exec_data)
		(*data)->list_exec_data = (*data)->exec_data;
	else
	{
		put_last(&((*data)->list_exec_data), (*data)->exec_data);
		(*data)->exec_data = NULL;
	}
	if (create)
	{
		(*data)->exec_data = exec_data_init();
		if (!(*data)->exec_data)
			return (MALLOC_ERROR);
	}
	return (OK);
}
