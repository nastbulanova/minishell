/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exp_field_utils_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:27:34 by akitsenk          #+#    #+#             */
/*   Updated: 2025/03/01 12:32:41 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Retrieves the value of an environment variable.
 *
 * Searches the minishell environment for a variable matching the given name.
 * Returns a duplicated string of the variable's value or an empty string if
 * not found.
 *
 * @param data Pointer to the minishell data.
 * @param name The name of the environment variable.
 * @return A duplicated string with the variable's value, or an empty string.
 */
char	*env_var_replace(t_minishell *data, char *name)
{
	t_env	*head;
	char	*var_value;

	if (!name)
		return (NULL);
	head = data->env;
	while (head)
	{
		if (!ft_strncmp(head->name, name, ft_strlen(name) + 1))
		{
			if (!head->value)
				var_value = ft_strdup("");
			else
				var_value = ft_strdup(head->value);
			return (var_value);
		}
		head = head->next;
	}
	var_value = ft_strdup("");
	return (var_value);
}

/**
 * @brief Expands a variable if in unquoted or double quoted context.
 *
 * If the variable is "$?", returns the exit code as a string.
 * Otherwise extracts the variable name and returns its value.
 *
 * @param data Pointer to minishell data.
 * @param input The input string.
 * @param i Pointer to the current index.
 * @return The expanded variable value, or NULL on failure.
 */
char	*expand_variable(t_minishell *data, const char *input, int *i)
{
	char	*var_name;
	char	*var_value;
	int		start;
	int		j;

	if (input[*i + 1] == '?')
	{
		*i = *i + 2;
		return (ft_itoa(data->exit_code));
	}
	start = *i + 1;
	j = start;
	while (input[j] != '\0' && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	var_name = ft_substr(input, start, j - start);
	if (var_name == NULL)
		return (NULL);
	if (ft_strlen(var_name) == 0)
		return (*i = j, free(var_name), ft_strdup("$"));
	var_value = env_var_replace(data, var_name);
	free(var_name);
	*i = j;
	return (var_value);
}

/**
 * @brief Processes an unquoted segment.
 *
 * Copies characters until a quote or '$' is encountered.
 *
 * @param input The input string.
 * @param i Pointer to the current index.
 * @return A new string with the copied segment, or NULL on failure.
 */
char	*process_unquoted(const char *input, int *i)
{
	char	*res;

	res = NULL;
	res = ft_strdup("");
	if (!res)
		return (NULL);
	while (input[*i] != '\0' && input[*i] != '\''
		&& input[*i] != '"' && input[*i] != '$')
	{
		res = append_char_to_str(res, input[*i]);
		if (res == NULL)
			return (NULL);
		(*i)++;
	}
	return (res);
}
