/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_opt_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:59:22 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/11 13:43:18 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Creates an option linked list node.
 *
 * Allocates and initializes a t_opt_llist node with the given option string.
 * 
 * @param opt The option string.
 * @return Pointer to the new node, or NULL if allocation fails.
 */
t_opt_llist	*opt_create(char *opt)
{
	t_opt_llist	*tmp;

	tmp = (t_opt_llist *)malloc(sizeof(t_opt_llist));
	if (!tmp)
		return (NULL);
	tmp->opt = opt;
	tmp->next = NULL;
	return (tmp);
}

/**
 * @brief Adds an option to the execution data's option list.
 *
 * Creates a new option node and appends it to the end of the option list.
 * 
 * @param data Pointer to the minishell data structure pointer.
 * @param opt The option string.
 * @return OK on success, or MALLOC_ERROR on failure.
 */
t_parser_error	opt_add(t_minishell **data, char *opt)
{
	t_opt_llist	*new;
	t_opt_llist	*current;

	if (!opt)
		return (MALLOC_ERROR);
	if (*opt == '\0')
		return (free(opt), OK);
	new = opt_create(opt);
	if (!(*data)->exec_data->opt_llist)
		(*data)->exec_data->opt_llist = new;
	else
	{
		current = (*data)->exec_data->opt_llist;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (OK);
}
