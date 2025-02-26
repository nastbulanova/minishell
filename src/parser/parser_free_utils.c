/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:55:05 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/26 17:32:45 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Frees a redirection list.
 *
 * Iterates over the redirection list and frees each node.
 * Sets the redirection pointer to NULL afterwards.
 *
 * @param redirs Pointer to the redirection list.
 */
void	free_redirs(t_redir **redirs)
{
	t_redir	*curr;
	t_redir	*next;

	curr = *redirs;
	while (curr)
	{
		next = curr->next;
		free(curr->str);
		if (curr->error)
			free(curr->error);
		free(curr);
		curr = next;
	}
	*redirs = NULL;
}

/**
 * @brief Frees an options linked list.
 *
 * Iterates through the options list, freeing each option string and node.
 * Sets the options pointer to NULL after freeing.
 *
 * @param opt_llist Pointer to the options list.
 */
void	free_opt_llist(t_opt_llist **opt_llist)
{
	t_opt_llist	*curr;
	t_opt_llist	*next;

	curr = *opt_llist;
	while (curr)
	{
		next = curr->next;
		if (curr->opt)
			free(curr->opt);
		free(curr);
		curr = next;
	}
	*opt_llist = NULL;
}

/**
 * @brief Frees execution data.
 *
 * Frees the command, options, redirections, and closes file descriptors.
 * Finally frees the execution data structure and sets its pointer to NULL.
 *
 * @param tmp_exec_data Pointer to the execution data.
 */
void	free_exec_data(t_exec_data *tmp_exec_data)
{
	if (tmp_exec_data->cmd)
	{
		free(tmp_exec_data->cmd);
		tmp_exec_data->cmd = NULL;
	}
	free_opt_llist(&(tmp_exec_data->opt_llist));
	free_redirs(&(tmp_exec_data->redirs));
	if (tmp_exec_data->opt)
	{
		free_array(tmp_exec_data->opt, NULL);
		tmp_exec_data->opt = NULL;
	}
	free_array(tmp_exec_data->opt, NULL);
	close_fd(&tmp_exec_data->output_fd);
	close_fd(&tmp_exec_data->input_fd);
	close_pipe(tmp_exec_data->outpipe);
	free(tmp_exec_data);
	tmp_exec_data = NULL;
}

/**
 * @brief Frees parser data.
 *
 * Frees the execution data list and token list from the minishell structure.
 * Sets the corresponding pointers to NULL after freeing.
 *
 * @param data Pointer to the minishell data structure pointer.
 */
void	free_parser_data(t_minishell **data)
{
	t_token		*tmp_token;
	t_exec_data	*tmp_exec_data;

	while ((*data)->list_exec_data)
	{
		tmp_exec_data = (*data)->list_exec_data;
		(*data)->list_exec_data = (*data)->list_exec_data->next;
		free_exec_data(tmp_exec_data);
		tmp_exec_data = NULL;
	}
	(*data)->list_exec_data = NULL;
	while ((*data)->token_head)
	{
		tmp_token = (*data)->token_head;
		(*data)->token_head = (*data)->token_head->next;
		free(tmp_token->start);
		tmp_token->start = NULL;
		free(tmp_token);
		tmp_token = NULL;
	}
	(*data)->token_head = NULL;
}
