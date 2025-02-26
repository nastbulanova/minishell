/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:27:23 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/26 15:58:40 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Extracts the name part of an environment variable string.
 * 
 * This function extracts the variable name from a given string formatted as
 * "NAME=VALUE". It allocates memory for the name and returns it as a new string.
 * 
 * @param str The input string containing the environment variable.
 * @return A newly allocated string containing the variable name, or NULL 
 * on failure.
 * 
 * @note The caller is responsible for freeing the returned string.
 */
static char	*env_name_extract(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_calloc(i + 1, sizeof(char));
	if (!name)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		name[i] = str[i];
		i++;
	}
	return (name);
}

/**
 * @brief Extracts the value part of an environment variable string.
 * 
 * This function extracts the value portion from a string formatted as 
 * "NAME=VALUE".
 * It allocates memory for the value and returns it as a new string.
 * 
 * @param str The input string containing the environment variable.
 * @return A newly allocated string containing the variable value, or 
 * NULL on failure.
 * 
 * @note The caller is responsible for freeing the returned string.
 */
static char	*env_value_extract(char *str)
{
	int		string_len;
	int		i;
	int		j;
	char	*value;

	string_len = ft_strlen(str);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	value = ft_calloc(string_len - i, sizeof(char));
	if (!value)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		value[j++] = str[i++];
	return (value);
}

/**
 * @brief Extracts the name and value from an environment variable string.
 * 
 * This function parses an environment variable formatted as "NAME=VALUE" and
 * creates a t_env struct containing separate dynamically allocated name 
 * and value strings.
 * 
 * @param str The input string containing the environment variable.
 * @return A pointer to a newly allocated t_env structure, or NULL on failure.
 * 
 * @note The caller is responsible for freeing the allocated t_env structure 
 * and its fields.
 */
t_env	*env_extract(char *str)
{
	char	*equal_pos;
	t_env	*result;

	equal_pos = ft_strchr(str, '=');
	if (equal_pos == NULL || equal_pos == str)
		return (NULL);
	result = ft_calloc(1, sizeof(t_env));
	if (!result)
		return (NULL);
	result->name = env_name_extract(str);
	result->value = env_value_extract(str);
	return (result);
}
