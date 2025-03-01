/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:02:39 by akitsenk          #+#    #+#             */
/*   Updated: 2025/03/01 20:12:48 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Processes tokens until a PIPE token is encountered.
 *
 * Iterates through tokens, handling words, redirections, and heredocs.
 * Returns an error if a syntax or memory issue is detected.
 *
 * @param data Pointer to the minishell data structure.
 * @param token Pointer to the current token pointer.
 * @param cmd Pointer to the command flag.
 * @return OK on success or an error code.
 */
t_parser_error	parser_loop(t_minishell *data, t_token **token, int *cmd)
{
	char				*tmp;
	t_parser_error		error;

	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type == WORD || (*token)->type == ENV_VAR)
		{
			tmp = open_field(data, *token);
			if (!(data->exec_data->cmd))
				error = cmd_check(&data, tmp, &cmd);
			error = opt_add(&data, tmp);
			tmp = NULL;
		}
		else if ((*token)->type >= REDIR_OUT && (*token)->type <= REDIR_APPEND)
			error = redir_check(&data, &token);
		else
			error = heredoc_check(&data, &token);
		if (error == OK)
			*token = (*token)->next;
		else
			return (error);
	}
	return (error);
}

/**
 * @brief Handles PIPE tokens within the command sequence.
 *
 * Validates pipe usage and appends execution data accordingly.
 * Returns a syntax error if pipe usage is invalid.
 *
 * @param data Pointer to the minishell data structure.
 * @param token Pointer to the current token pointer.
 * @param cmd Pointer to the command flag.
 * @return OK on success or an error code.
 */
static t_parser_error	handle_pipe(t_minishell *data, t_token **token,
	int *cmd)
{
	if (token && *token && (*token)->type == PIPE)
	{
		if (!(data->exec_data->cmd) && !(*token)->next)
			return (SYNTAX_ERROR);
		if ((*token)->next)
		{
			*cmd = 0;
			(*token) = (*token)->next;
			return (exec_data_append(&data, 1));
		}
	}
	else
		return (exec_data_append(&data, 0));
	return (OK);
}

/**
 * @brief Main parser function.
 *
 * Initializes execution data and processes tokens by calling parser_loop and
 * handle_pipe. Returns syntax or memory errors if encountered.
 *
 * @param data Pointer to the minishell data structure.
 * @return OK on success or an error code.
 */
t_parser_error	parser(t_minishell *data)
{
	t_token			*token;
	int				cmd;
	t_parser_error	error;

	(data)->exec_data = exec_data_init();
	token = data->token_head;
	while (token)
	{
		cmd = 0;
		error = OK;
		error = parser_loop(data, &token, &cmd);
		if (error == SYNTAX_ERROR)
			return (syntax_error(&data, &token));
		else if (error == MALLOC_ERROR)
			return (memory_error(&data));
		else
		{
			error = handle_pipe(data, &token, &cmd);
			if (error == SYNTAX_ERROR)
				return (syntax_error(&data, &token));
			if (error == MALLOC_ERROR)
				return (memory_error(&data));
		}
	}
	return (OK);
}
