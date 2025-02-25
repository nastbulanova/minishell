/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exp_field_utils_0.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:25:14 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/25 11:20:54 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Processes a quoted segment.
 *
 * Processes a segment enclosed by the given quote.
 * In double quotes, variable expansion is performed;
 * in single quotes, the content is taken literally.
 *
 * @param data Pointer to minishell data.
 * @param input The input string.
 * @param i Pointer to the current index (at opening quote).
 * @param quote The quote character.
 * @return A new string with the processed segment, or NULL on failure.
 */
static char	*process_quote(t_minishell *data, const char *input, int *i,
	char quote)
{
	char	*res;
	char	*temp;

	res = ft_strdup("");
	if (res == NULL)
		return (NULL);
	(*i)++;
	while (input[*i] != '\0' && input[*i] != quote)
	{
		if (quote == '"' && input[*i] == '$')
		{
			temp = expand_variable(data, input, i);
			res = append_str_to_str(res, temp);
			free(temp);
		}
		else
		{
			res = append_char_to_str(res, input[*i]);
			(*i)++;
		}
	}
	if (input[*i] == quote)
		(*i)++;
	return (res);
}

/**
 * @brief Processes an unquoted segment and appends its result.
 *
 * Calls process_unquoted, then appends the returned string to result.
 *
 * @param input The input string.
 * @param i Pointer to the current index.
 * @param result Pointer to the result string.
 * @return OK on success, or MALLOC_ERROR on failure.
 */
static t_parser_error	process_unquoted_segment(const char *input, int *i,
	char **result)
{
	char	*temp;

	temp = process_unquoted(input, i);
	if (temp == NULL)
		return (MALLOC_ERROR);
	*result = append_str_to_str(*result, temp);
	free(temp);
	return (OK);
}

/**
 * @brief Processes a special segment (quoted or variable) and appends its
 * result.
 *
 * If the current character is a quote or '$', processes it accordingly.
 *
 * @param data Pointer to minishell data.
 * @param input The input string.
 * @param i Pointer to the current index.
 * @param result Pointer to the result string.
 * @return OK on success, or MALLOC_ERROR on failure.
 */
t_parser_error	process_special_segment(t_minishell *data,
						const char *input, int *i, char **result)
{
	char	*temp;

	if (input[*i] == '\'' || input[*i] == '"')
	{
		temp = process_quote(data, input, i, input[*i]);
		if (temp == NULL)
			return (MALLOC_ERROR);
		*result = append_str_to_str(*result, temp);
		free(temp);
	}
	else if (input[*i] == '$')
	{
		temp = expand_variable(data, input, i);
		if (temp == NULL)
			return (MALLOC_ERROR);
		*result = append_str_to_str(*result, temp);
		free(temp);
	}
	return (OK);
}

/**
 * @brief Expands a field string with Bash-like quoting rules.
 *
 * Processes unquoted text, then special segments (quotes and variables).
 * Variables are expanded only in double quotes or unquoted text.
 *
 * @param data Pointer to minishell data.
 * @param input The input field string.
 * @return The expanded string, or NULL on failure.
 */
char	*expand_field_string(t_minishell *data, const char *input)
{
	int				i;
	char			*result;
	t_parser_error	err;

	i = 0;
	result = NULL;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (input[i] != '\0')
	{
		err = process_unquoted_segment(input, &i, &result);
		if (err != OK)
			return (free(result), NULL);
		if (input[i] == '\0')
			break ;
		err = process_special_segment(data, input, &i, &result);
		if (err != OK)
			return (free(result), NULL);
	}
	return (result);
}

/**
 * @brief Expands a token field.
 *
 * Processes the token's string using Bash-like expansion rules.
 * Outer quotes are removed while inner quotes are preserved.
 * In single quotes, no variable expansion is performed.
 *
 * @param data Pointer to minishell data.
 * @param token Pointer to the token to be expanded.
 * @return The expanded string, or NULL on failure.
 */
char	*open_field(t_minishell *data, t_token *token)
{
	char	*input;
	char	*final_str;

	input = NULL;
	final_str = NULL;
	input = ft_substr(token->start, 0, token->len);
	if (!input)
		return (NULL);
	if (dirty_check(token))
		final_str = ft_strdup("$");
	else
		final_str = expand_field_string(data, input);
	free(input);
	return (final_str);
}
