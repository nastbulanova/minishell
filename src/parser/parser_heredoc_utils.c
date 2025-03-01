/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:57:05 by akitsenk          #+#    #+#             */
/*   Updated: 2025/03/01 00:01:56 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Counts the number of quotes in a string.
 *
 * Iterates through the first len characters and counts both single and double
 * quotes.
 *
 * @param str Input string.
 * @param len Number of characters to examine.
 * @return The total count of quotes.
 */
int	count_quotes(char *str, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		if (str[i] == '\"' || str[i] == '\'')
			count++;
		i++;
	}
	return (count);
}

/**
 * @brief Removes quotes from a string.
 *
 * Allocates a new string excluding any single or double quotes and sets *type
 * to FIELD if a quote is found.
 *
 * @param str Input string.
 * @param len Length of the string.
 * @param type Pointer to a token type.
 * @return The new string without quotes, or NULL on failure.
 */
char	*remove_quotes(char *str, int len, t_token_type *type)
{
	int		quotes_count;
	int		i;
	int		j;
	char	*new_str;

	quotes_count = count_quotes(str, len);
	new_str = (char *)malloc(((len - quotes_count) + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] != '\"' && str[i] != '\'')
		{
			new_str[j] = str[i];
			j++;
		}
		else
			*type = FIELD;
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}

/**
 * @brief Checks heredoc syntax and processes the next token.
 *
 * Validates the next token in heredoc mode, removes quotes if needed, and adds
 * a redirection.
 *
 * @param data Pointer to the minishell data structure pointer.
 * @param token Triple pointer to the current token.
 * @return OK on success, or SYNTAX_ERROR/MALLOC_ERROR on failure.
 */
t_parser_error	heredoc_check(t_minishell **data, t_token ***token)
{
	t_token_type	type;
	char			*str;
	t_token			**next;

	type = NOT_EXIST;
	str = NULL;
	if ((**token)->next)
	{
		next = &(**token)->next;
		if ((*next)->type == WORD)
			str = remove_quotes((*next)->start, (*next)->len, &type);
		else
			return (SYNTAX_ERROR);
		if (!str)
			return (MALLOC_ERROR);
		if (type == NOT_EXIST)
			type = WORD;
		if (redir_add(&data, str, type, 2) == OK)
			return ((**token) = (**token)->next, OK);
		else
			return (MALLOC_ERROR);
	}
	else
		return (SYNTAX_ERROR);
	return (OK);
}
