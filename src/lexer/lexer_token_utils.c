/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:35:13 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/26 17:15:21 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Creates a new token.
 *
 * Allocates a token structure, duplicates the string of given length,
 * and sets its type. Returns NULL on allocation failure.
 *
 * @param start The source string for the token.
 * @param len The length of the token.
 * @param type The token type.
 * @return Pointer to the new token, or NULL if allocation fails.
 */
t_token	*token_create(char *start, int len, int type)
{
	t_token	*tmp;

	tmp = NULL;
	tmp = (t_token *)malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	if (len == 0)
	{
		start = ft_strdup("");
		if (!start)
			return (NULL);
	}
	tmp->start = ft_substr(start, 0, len);
	if (!tmp->start)
		return (NULL);
	tmp->len = len;
	tmp->type = type;
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

/**
 * @brief Appends a token to the token list.
 *
 * Adds the token at the end of the token list.
 *
 * @param token_head Pointer to the head of the token list.
 * @param token The token to append.
 */
void	token_append(t_token **token_head, t_token *token)
{
	t_token	*current;

	if (*token_head == NULL)
		*token_head = token;
	else
	{
		current = *token_head;
		while (current->next)
			current = current->next;
		current->next = token;
	}
}

/**
 * @brief Creates and adds a token to the token list.
 *
 * Calls token_create to allocate a new token and appends it.
 * Returns OK on success, or MALLOC_ERROR on failure.
 *
 * @param token_head Pointer to the token list head.
 * @param start The source string for the token.
 * @param len The length of the token.
 * @param type The token type.
 * @return OK if successful, or MALLOC_ERROR.
 */
t_parser_error	token_add(t_token **token_head, char *start, int len,
	t_token_type type)
{
	t_token	*new;

	new = NULL;
	new = token_create(start, len, type);
	if (!new)
		return (MALLOC_ERROR);
	token_append(token_head, new);
	return (OK);
}

/**
 * @brief Checks if the last token in the list is a pipe.
 *
 * Traverses the token list and returns 1 if the last token's type is PIPE,
 * otherwise returns 0.
 *
 * @param head Pointer to the head of the token list.
 * @return 1 if the last token is PIPE, or 0 otherwise.
 */
int	is_last_token_pipe(t_token *head)
{
	t_token	*current;

	current = head;
	if (!current)
		return (0);
	while (current->next)
		current = current->next;
	return (current->type == PIPE);
}

/**
 * @brief Tokenizes an input string into a list of tokens.
 *
 * Iterates over the string, using check_char() to build tokens.
 * On success, appends the token list; on error, cleans up tokens.
 *
 * @param token_head Pointer to the head of the token list.
 * @param line The input string to tokenize.
 * @return OK on success or an error code.
 */
t_parser_error	tokenize_str(t_token **token_head, char *line)
{
	int				i;
	t_parser_error	error;
	t_token			*token;

	error = OK;
	token = NULL;
	i = 0;
	while (line[i] != '\0' && error == OK)
		error = check_char(&token, line, &i);
	if (error == OK)
		token_append(token_head, token);
	else
		token_clean(token);
	return (error);
}
