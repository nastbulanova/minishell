/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:33:49 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/18 12:16:03 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Cleans up the token list.
 *
 * Frees memory for each token and its string.
 *
 * @param token_head Pointer to the head of the token list.
 */
void	token_clean(t_token *token_head)
{
	t_token	*tmp_token;

	while (token_head)
	{
		tmp_token = token_head;
		token_head = token_head->next;
		free(tmp_token->start);
		tmp_token->start = NULL;
		free(tmp_token);
		tmp_token = NULL;
	}
}

/**
 * @brief Handles lexer errors.
 *
 * Prints an error message based on the error code, cleans the token list,
 * and returns OK if the error is CTRLC.
 *
 * @param token_head Pointer to the token list.
 * @param error The lexer error code.
 * @return OK if error is CTRLC, otherwise the original error.
 */
t_parser_error	lexer_error(t_token *token_head, t_parser_error error)
{
	if (error == SYNTAX_ERROR)
		printf("minishell: syntax error: unclosed quote\n");
	else if (error == MALLOC_ERROR)
		printf("minishell: malloc error\n");
	else if (error == PIPE_ERROR)
		printf("minishell: pipe error\n");
	else if (error == CLOSE_FD_ERROR)
		printf("minishell: close fd error\n");
	token_clean(token_head);
	return (error);
}
