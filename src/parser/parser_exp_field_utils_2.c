/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exp_field_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:02:02 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/26 11:17:49 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Appends a single character to a string.
 *
 * Allocates a new string with the appended character,
 * frees the old string, and returns the new string.
 *
 * @param s The original string.
 * @param c The character to append.
 * @return The new string, or NULL on failure.
 */
char	*append_char_to_str(char *s, char c)
{
	char	*new_str;
	int		len;
	int		i;

	if (!s || !c)
		return (NULL);
	len = 0;
	len = ft_strlen(s);
	new_str = NULL;
	new_str = (char *)malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (free(s), NULL);
	i = 0;
	while (s[i] != '\0')
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(s);
	return (new_str);
}

/**
 * @brief Appends one string to another.
 *
 * Joins s and t, frees s, and returns the concatenated string.
 *
 * @param s The original string.
 * @param t The string to append.
 * @return The concatenated string, or NULL on failure.
 */
char	*append_str_to_str(char *s, const char *t)
{
	char	*new_str;

	if (!s || !t)
		return (NULL);
	new_str = NULL;
	new_str = ft_strjoin(s, t);
	free(s);
	if (!new_str)
		return (NULL);
	return (new_str);
}
