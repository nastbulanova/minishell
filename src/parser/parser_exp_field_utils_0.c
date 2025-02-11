/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exp_field_utils_test.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:53:03 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/11 14:06:09 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Initializes a new expansion field.
 *
 * Allocates and sets default values for a t_exp_field structure.
 *
 * @param data Pointer to the minishell data structure.
 * @return Pointer to the initialized field, or NULL on failure.
 */
static t_exp_field	*init_field(t_minishell *data)
{
	t_exp_field	*field;

	field = NULL;
	field = (t_exp_field *)malloc(sizeof(t_exp_field));
	if (!field)
		return (NULL);
	field->i = 0;
	field->j = 0;
	field->start = 0;
	field->data = data;
	field->result = ft_strdup("");
	if (!field->result)
	{
		free(field);
		return (NULL);
	}
	return (field);
}

/**
 * @brief Finalizes a substring expansion.
 *
 * Extracts a substring from 'str' based on current indices and appends it to
 * the result.
 *
 * @param f Pointer to the expansion field.
 * @param str The input string.
 * @return OK on success, or MALLOC_ERROR if memory allocation fails.
 */
static t_parser_error	finalize_substr(t_exp_field *f, char *str)
{
	t_parser_error	error;
	char			*frag;
	char			*joined;
	int				len;

	error = OK;
	len = f->i - f->start;
	frag = ft_substr(str, f->start, len);
	if (!frag)
		return (MALLOC_ERROR);
	joined = ft_strjoin(f->result, frag);
	free(frag);
	free(f->result);
	if (!joined)
		return (MALLOC_ERROR);
	f->result = joined;
	return (error);
}

/**
 * @brief Fills the expansion field with processed data.
 *
 * Processes the input string by expanding variables and quotes.
 *
 * @param f Pointer to the expansion field.
 * @param str The input string.
 * @param len Length of the input string.
 * @return OK on success, or an error code on failure.
 */
static t_parser_error	fill_field(t_exp_field *f, char *str, int len)
{
	t_parser_error	error;

	error = OK;
	while (f->i < len && error == OK)
	{
		if (str[f->i] == '$' && (f->i + 1 < len) && str[f->i + 1] == '?')
			error = end_code_exp(&f, str);
		else if (str[f->i] == '$' && (f->i + 1 < len) && str[f->i + 1] != ' '
			&& str[f->i + 1] != '$')
			error = env_var_exp(&f, str);
		else if (str[f->i] == '\'' || str[f->i] == '"')
		{
			error = finalize_substr(f, str);
			if (error != OK)
				break ;
			error = handle_quotes(f, str, str[f->i]);
			f->i++;
			f->start = f->i;
		}
		else
			f->i++;
	}
	return (error);
}

/**
 * @brief Finalizes the expansion field.
 *
 * Appends any remaining substring to the result and returns the final string.
 *
 * @param field Pointer to the expansion field.
 * @param str The input string.
 * @return The final expanded string, or NULL on failure.
 */
static char	*finalize_field(t_exp_field *field, char *str)
{
	t_parser_error	err;
	char			*res;

	err = finalize_substr(field, str);
	if (err != OK)
	{
		free(field->result);
		return (NULL);
	}
	res = field->result;
	return (res);
}

/**
 * @brief Expands a token field.
 *
 * Processes the token's string using expansion rules and returns the expanded
 * result.
 *
 * @param data Pointer to the minishell data structure.
 * @param token Pointer to the token to be expanded.
 * @return The expanded string, or NULL on failure.
 */
char	*open_field(t_minishell *data, t_token *token)
{
	t_exp_field		*field;
	t_parser_error	error;
	char			*final_str;
	int				length;

	field = NULL;
	field = init_field(data);
	if (!field)
		return (NULL);
	length = token->len;
	error = fill_field(field, token->start, length);
	if (error != OK)
	{
		free(field->result);
		free(field);
		return (NULL);
	}
	final_str = finalize_field(field, token->start);
	if (!final_str)
		return (free(field), NULL);
	return (free(field), final_str);
}
