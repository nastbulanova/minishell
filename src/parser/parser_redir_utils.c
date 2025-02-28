/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:01:13 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/28 11:01:26 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Creates a new redirection node.
 *
 * Allocates and initializes a t_redir node with the given string and type.
 * Determines the redirection type based on the provided token type.
 *
 * @param str The redirection string.
 * @param type The token type to decide the redirection type.
 * @return Pointer to the new redirection node, or NULL on failure.
 */
t_redir	*redir_create(char *str, t_token_type type)
{
	t_redir	*tmp;

	tmp = (t_redir *)malloc(sizeof(t_redir));
	if (!tmp)
		return (free(str), NULL);
	tmp->str = str;
	if (type == REDIR_OUT)
		tmp->type = OUTPUT;
	else if (type == REDIR_IN)
		tmp->type = INPUT;
	else if (type == REDIR_APPEND)
		tmp->type = OUTPUT_APPEND;
	else if (type == WORD)
		tmp->type = HEREDOC;
	else
		tmp->type = HEREDOC_QUOTED;
	tmp->error = NULL;
	tmp->next = NULL;
	return (tmp);
}

/**
 * @brief Adds a redirection node to the execution data.
 *
 * Creates a new redirection node and appends it to the redirs list of exec_data.
 *
 * @param data Triple pointer to the minishell data structure.
 * @param str The redirection string.
 * @param type The token type for redirection.
 * @return OK on success, or MALLOC_ERROR on failure.
 */
t_parser_error	redir_add(t_minishell ***data, char *str, int type)
{
	t_redir	*new;
	t_redir	*current;

	if (!str)
		return (MALLOC_ERROR);
	new = redir_create(str, type);
	if (!new)
		return (MALLOC_ERROR);
	if (!(**data)->exec_data->redirs)
		(**data)->exec_data->redirs = new;
	else
	{
		current = (**data)->exec_data->redirs;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (OK);
}

/**
 * @brief Checks and processes a redirection token.
 *
 * Validates the next token for a redirection, removes quotes if necessary,
 * and adds the resulting string as a redirection node.
 *
 * @param data Pointer to the minishell data structure pointer.
 * @param token Triple pointer to the current token.
 * @return OK on success, or an error code on failure.
 */
t_parser_error	redir_check(t_minishell **data, t_token ***token)
{
	char	*str;
	t_token	**next;

	str = NULL;
	next = NULL;
	if ((**token)->next && (**token)->next->type == WORD)
	{
		next = &(**token)->next;
		str = open_field(*data, *next);
		if (!str)
			return (MALLOC_ERROR);
		if (*str == '\0')
		{
			free(str);
			str = ft_substr((*next)->start, 0, (*next)->len);
			printf("redir name %s", str);
		}
		if (!str)
			return (MALLOC_ERROR);
	}
	else
		return (SYNTAX_ERROR);
	if (redir_add(&data, str, (**token)->type) == OK)
		return ((**token) = (**token)->next, OK);
	else
		return (MALLOC_ERROR);
}
