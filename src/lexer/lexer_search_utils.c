/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_search_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:33:37 by akitsenk          #+#    #+#             */
/*   Updated: 2025/03/01 20:11:22 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Processes a quoted segment to find the closing quote.
 *
 * Increments the index until the matching quote is found and adjusts the length.
 *
 * @param line The input string.
 * @param func Function pointer to check the quote character.
 * @param i Triple pointer to the current index.
 * @param len Pointer to the length counter.
 * @return 1 if the closing quote is found, -1 if not.
 */
int	second_quote(char *line, int (*func)(int), int ***i, int *len)
{
	int	secondquote;

	secondquote = -1;
	(***i)++;
	while (line[***i] != '\0')
	{
		if (func(line[***i]))
		{
			secondquote = 1;
			(*len) += 2;
			(***i)++;
			break ;
		}
		(*len)++;
		(***i)++;
	}
	return (secondquote);
}

/**
 * @brief Processes a sequence of word characters.
 *
 * Scans the input line for a sequence of word characters while handling quotes.
 *
 * @param token_head Pointer to the token list head.
 * @param line The input string.
 * @param i Double pointer to the current index.
 * @return OK on success or SYNTAX_ERROR if an unclosed quote is encountered.
 */
t_parser_error	while_sequence(t_token **token_head, char *line, int **i)
{
	int	start;
	int	len;
	int	secondquote;

	start = **i;
	len = 0;
	secondquote = **i;
	while (line[**i] != '\0' && ft_iswordchar(line[**i]))
	{
		if (ft_isquote(line[**i]))
			secondquote = second_quote(line, ft_isquote, &i, &len);
		else if (ft_isdblquote(line[**i]))
			secondquote = second_quote(line, ft_isdblquote, &i, &len);
		else
		{
			len++;
			(**i)++;
		}
		if (secondquote == -1)
			return (SYNTAX_ERROR);
	}
	return (token_add(token_head, &(line[start]), len, WORD));
}

/**
 * @brief Finds a redirection token in the input.
 *
 * Determines if the redirection is single or double and adds it as a token.
 *
 * @param token_head Pointer to the token list head.
 * @param line The input string.
 * @param c The redirection character ('>' or '<').
 * @param i Double pointer to the current index.
 * @return OK on success.
 */
t_parser_error	find_redir(t_token **token_head, char *line, char c, int **i)
{
	t_token_type	type;
	int				start;

	start = **i;
	if (c == '>')
		type = REDIR_OUT;
	else
		type = REDIR_IN;
	if (line[**i + 1] == c)
	{
		(**i) += 2;
		return (token_add(token_head, &(line[start]), 2, type + 2));
	}
	else
	{
		(**i)++;
		return (token_add(token_head, &(line[start]), 1, type));
	}
}

int	while_var(char *line, int **i, int *var)
{
	int	start;
	int	len;

	start = **i;
	(**i)++;
	len = 1;
	while (line[**i] != '\0' && !ft_isspace(line[**i]))
	{
		if (!(ft_isalnum(line[**i])) && !(line[**i] == '_'))
			return (**i = start, 0);
		len++;
		(**i)++;
	}
	if (len > 1)
		*var = 1;
	else
		return (**i = start, 0);
	return (len);
}

/**
 * @brief Checks the current character and processes it accordingly.
 *
 * Dispatches to the appropriate function based on the character encountered.
 *
 * @param token_head Pointer to the token list head.
 * @param line The input string.
 * @param i Pointer to the current index.
 * @return OK on success.
 */
t_parser_error	check_char(t_token **token_head, char *line, int *i)
{
	int	len;
	int	var;
	int	start;

	var = 0;
	len = 0;
	if (line[*i] == '$' && line[*i + 1] != '?')
	{
		start = *i;
		len = while_var(line, &i, &var);
		if (var)
			return (token_add(token_head, &(line[start]), len, ENV_VAR));
	}
	if (ft_iswordchar(line[*i]) && var == 0)
		return (while_sequence(token_head, line, &i));
	else if (line[*i] == '>')
		return (find_redir(token_head, line, '>', &i));
	else if (line[*i] == '<')
		return (find_redir(token_head, line, '<', &i));
	else if (line[*i] == '|')
		return ((*i)++, token_add(token_head, &(line[(*i) - 1]), 1, PIPE));
	else
		(*i)++;
	return (OK);
}
