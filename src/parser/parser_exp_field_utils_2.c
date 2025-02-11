/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exp_field_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:02:02 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/11 15:17:07 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Processes a single quoted fragment.
 *
 * Appends the extracted fragment to the result stored in the expansion field.
 *
 * @param f Pointer to the expansion field.
 * @param frag The fragment extracted from single quotes.
 * @return OK on success, or MALLOC_ERROR if allocation fails.
 */
static t_parser_error	process_single_quote(t_exp_field *f, char *frag)
{
	t_parser_error	error;
	char			*tmp;

	error = OK;
	tmp = ft_strjoin(f->result, frag);
	free(frag);
	free(f->result);
	if (tmp == NULL)
		return (MALLOC_ERROR);
	f->result = tmp;
	return (error);
}

/**
 * @brief Processes a double quoted fragment.
 *
 * Expands the fragment (processing environment variables) and appends it to
 * the result.
 *
 * @param f Pointer to the expansion field.
 * @param frag The fragment extracted from double quotes.
 * @return OK on success, or MALLOC_ERROR if allocation fails.
 */
static t_parser_error	process_double_quote(t_exp_field *f, char *frag)
{
	t_parser_error	error;
	char			*tmp;
	char			*new_frag;
	t_token			tmp_token;

	error = OK;
	tmp_token.start = frag;
	tmp_token.len = (int)ft_strlen(frag);
	tmp_token.type = WORD;
	tmp_token.group = 0;
	tmp_token.prev = NULL;
	tmp_token.next = NULL;
	tmp = open_field(f->data, &tmp_token);
	free(frag);
	if (tmp == NULL)
		return (MALLOC_ERROR);
	new_frag = ft_strjoin(f->result, tmp);
	free(tmp);
	free(f->result);
	if (new_frag == NULL)
		return (MALLOC_ERROR);
	f->result = new_frag;
	return (error);
}

/**
 * @brief Handles quoted substrings.
 *
 * Extracts the fragment enclosed by the given quote and processes it
 * accordingly.
 *
 * @param f Pointer to the expansion field.
 * @param str The input string.
 * @param quote The quote character (' or ").
 * @return OK on success, or MALLOC_ERROR if memory allocation fails.
 */
t_parser_error	handle_quotes(t_exp_field *f, char *str, char quote)
{
	t_parser_error	error;
	char			*frag;
	int				start_pos;
	int				len;

	error = OK;
	start_pos = f->i + 1;
	f->i = f->i + 1;
	while (str[f->i] != '\0' && str[f->i] != quote)
		f->i = f->i + 1;
	len = f->i - start_pos;
	frag = ft_substr(str, start_pos, len);
	if (frag == NULL)
		return (MALLOC_ERROR);
	if (quote == '\'')
		error = process_single_quote(f, frag);
	else
		error = process_double_quote(f, frag);
	return (error);
}
