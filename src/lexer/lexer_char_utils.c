/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_char_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:33:57 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/11 13:39:17 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Checks if a character is a whitespace.
 *
 * Returns true if c is a tab, carriage return, or space.
 *
 * @param c The character to check.
 * @return 1 if c is whitespace, otherwise 0.
 */
int	ft_isspace(int c)
{
	return (c == 9 || c == 13 || c == 32);
}

/**
 * @brief Checks if a character is a word character.
 *
 * Returns true if c is printable, not a whitespace, and not '>', '<', or '|'.
 *
 * @param c The character to check.
 * @return 1 if c is a word character, otherwise 0.
 */
int	ft_iswordchar(int c)
{
	return (ft_isprint(c) && !ft_isspace(c) && c != '>'
		&& c != '<' && c != '|');
}

/**
 * @brief Checks if a character is a single quote.
 *
 * Returns true if c is the ASCII code for a single quote.
 *
 * @param c The character to check.
 * @return 1 if c is a single quote, otherwise 0.
 */
int	ft_isquote(int c)
{
	return (c == 39);
}

/**
 * @brief Checks if a character is a double quote.
 *
 * Returns true if c is the ASCII code for a double quote.
 *
 * @param c The character to check.
 * @return 1 if c is a double quote, otherwise 0.
 */
int	ft_isdblquote(int c)
{
	return (c == 34);
}
