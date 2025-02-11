/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exp_field_utils_1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:27:34 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/11 14:05:08 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Expands the exit code variable.
 *
 * Replaces the '$?' placeholder with the exit code value in the expansion field.
 * Updates the field indices accordingly.
 *
 * @param field Pointer to the expansion field pointer.
 * @param str The input string.
 * @return OK on success, or MALLOC_ERROR on allocation failure.
 */
t_parser_error	end_code_exp(t_exp_field **field, char *str)
{
	char	*code;
	char	*temp_result;
	char	*tmp;

	code = ft_itoa((*field)->data->exit_code);
	if (!code)
		return (MALLOC_ERROR);
	tmp = ft_substr(str, (*field)->start, (*field)->i - (*field)->start);
	if (!tmp)
		return (free(code), MALLOC_ERROR);
	temp_result = ft_strjoin((*field)->result, tmp);
	free(tmp);
	free((*field)->result);
	if (!temp_result)
		return (free(code), MALLOC_ERROR);
	(*field)->result = ft_strjoin(temp_result, code);
	free(temp_result);
	free(code);
	if (!(*field)->result)
		return (MALLOC_ERROR);
	(*field)->i += 1;
	(*field)->start = (*field)->i + 1;
	return (OK);
}

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
 * @brief Extracts an environment variable's value from the input string.
 *
 * Parses the variable name from the string starting after '$' and retrieves
 * its value.
 *
 * @param field Pointer to the expansion field pointer.
 * @param str The input string.
 * @return A duplicated string with the variable's value, or NULL on failure.
 */
char	*get_env_var_value(t_exp_field **field, char *str)
{
	char	*name;
	char	*var_value;

	(*field)->j = (*field)->i + 1;
	while (ft_isalpha(str[(*field)->j]) || str[(*field)->j] == '_'
		|| ft_isalnum(str[(*field)->j]))
		(*field)->j++;
	name = ft_substr(str, (*field)->i + 1, (*field)->j - (*field)->i - 1);
	if (!name)
		return (NULL);
	var_value = env_var_replace((*field)->data, name);
	free(name);
	return (var_value);
}

/**
 * @brief Expands an environment variable in the expansion field.
 *
 * Replaces the variable placeholder in the string with its value and updates
 * the field.
 *
 * @param field Pointer to the expansion field pointer.
 * @param str The input string.
 * @return OK on success, or MALLOC_ERROR on allocation failure.
 */
t_parser_error	env_var_exp(t_exp_field **field, char *str)
{
	char	*var_value;
	char	*temp_result;
	char	*substr_result;

	var_value = get_env_var_value(field, str);
	if (!var_value)
		return (MALLOC_ERROR);
	substr_result = ft_substr(str, (*field)->start, (*field)->i
			- (*field)->start);
	if (!substr_result)
		return (free(var_value), MALLOC_ERROR);
	temp_result = ft_strjoin((*field)->result, substr_result);
	free(substr_result);
	free((*field)->result);
	if (!temp_result)
		return (free(var_value), MALLOC_ERROR);
	(*field)->result = ft_strjoin(temp_result, var_value);
	free(var_value);
	free(temp_result);
	if (!(*field)->result)
		return (MALLOC_ERROR);
	(*field)->i = (*field)->j - 1;
	(*field)->start = (*field)->i + 1;
	return (OK);
}
