/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:49:54 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/11 17:50:01 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Handles a syntax error.
 *
 * Writes an error message with the unexpected token,
 * frees execution and parser data, and returns SYNTAX_ERROR.
 *
 * @param data Pointer to the minishell data structure pointer.
 * @param token Pointer to the token pointer.
 * @return SYNTAX_ERROR.
 */
t_parser_error	syntax_error(t_minishell **data, t_token **token)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	if ((*token)->next)
	{
		*token = (*token)->next;
		write(2, (*token)->start, (*token)->len);
	}
	else
		write(2, "\\n", 2);
	write(2, "'\n", 2);
	free_exec_data((*data)->exec_data);
	free_parser_data(data);
	return (SYNTAX_ERROR);
}

/**
 * @brief Handles a memory allocation error.
 *
 * Writes a memory error message, frees execution and parser data,
 * and returns MALLOC_ERROR.
 *
 * @param data Pointer to the minishell data structure pointer.
 * @return MALLOC_ERROR.
 */
t_parser_error	memory_error(t_minishell **data)
{
	write(2, "minishell: malloc error\n", 25);
	free_exec_data((*data)->exec_data);
	free_parser_data(data);
	return (MALLOC_ERROR);
}
