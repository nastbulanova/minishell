/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:29:15 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/26 15:58:17 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Calculates the required size for concatenating two 
 * arrays of strings.
 *
 * This function determines the total size needed to store the 
 * concatenation
 * of `split_pwd` and `split_arg`, including necessary separators.
 *
 * @param split_pwd First array of strings (e.g., representing a path 
 * split by '/').
 * @param split_arg Second array of strings to append.
 * @return The total required size in bytes.
 */
static size_t	get_arrays_size(char **split_pwd, char **split_arg)
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (split_pwd[i] && c_strcmp(split_pwd[i], split_arg[0]))
	{
		size += ft_strlen(split_pwd[i]) + 1;
		i++;
	}
	i = 0;
	while (split_arg[i])
	{
		size += ft_strlen(split_arg[i]) + 1;
		i++;
	}
	return (size);
}

/**
 * @brief Copies and concatenates two arrays of strings into a single 
 * buffer.
 *
 * This function constructs a new path-like string by appending `split_pwd`
 * to `split_arg`, adding '/' separators between components.
 *
 * @param result The destination buffer for the concatenated string.
 * @param split_pwd First array of strings (e.g., representing a path 
 * split by '/').
 * @param split_arg Second array of strings to append.
 */
static void	copy_arrays(char *result, char **split_pwd, char **split_arg)
{
	int		i;
	int		j;
	size_t	size;

	i = 0;
	size = 0;
	while (split_pwd[i] && c_strcmp(split_pwd[i], split_arg[0]))
	{
		j = 0;
		result[size++] = '/';
		while (split_pwd[i][j])
			result[size++] = split_pwd[i][j++];
		i++;
	}
	i = 0;
	while (split_arg[i])
	{
		j = 0;
		result[size++] = '/';
		while (split_arg[i][j])
			result[size++] = split_arg[i][j++];
		i++;
	}
}

/**
 * @brief Constructs a path string from two arrays of strings.
 *
 * This function allocates and returns a new string formed by concatenating
 * `split_pwd` and `split_arg` with '/' separators.
 *
 * @param split_pwd First array of strings (e.g., representing a path 
 * split by '/').
 * @param split_arg Second array of strings to append.
 * @return A dynamically allocated string representing the full path.
 */
char	*get_path_from_arrays(char **split_pwd, char **split_arg)
{
	char	*result;

	result = safe_malloc((get_arrays_size(split_pwd, split_arg) + 1)
			* sizeof(char));
	copy_arrays(result, split_pwd, split_arg);
	return (result);
}

/**
 * @brief Constructs a path string from a single array of strings.
 *
 * This function allocates and returns a new string formed by joining `split`
 * components with '/' separators.
 *
 * @param split Array of strings representing path components.
 * @return A dynamically allocated string representing the full path.
 */
char	*get_path_from_single_array(char **split)
{
	int		i;
	int		j;
	size_t	size;
	char	*result;

	size = 0;
	i = -1;
	while (split[++i])
		size += ft_strlen(split[i]) + 1;
	result = safe_malloc((size + 1) * sizeof(char));
	i = -1;
	while (split[++i])
	{
		size = 0;
		j = -1;
		if (i != 0)
			result[size++] = '/';
		while (split[i][++j])
		{
			result[size] = split[i][j];
			size++;
		}
	}
	return (result);
}

/**
 * @brief Generates a final path string from a sanitized argument path and
 *  the current working directory.
 *
 * If `sanitized_arg_path[0]` is "home", the function constructs the path
  using `get_path_from_single_array`.
 * Otherwise, it splits `pwd` into an array and constructs the path using 
 * `get_path_from_arrays`.
 *
 * @param sanitized_arg_path Array of strings representing the sanitized 
 * argument path.
 * @param pwd Current working directory as a string.
 * @return A dynamically allocated string representing the final path.
 */
char	*final_path_one(char **sanitized_arg_path, char *pwd)
{
	char	*final_path;
	char	**split_pwd;

	final_path = NULL;
	if (c_strcmp(sanitized_arg_path[0], "home") == 0)
		final_path = get_path_from_single_array(sanitized_arg_path);
	else
	{
		split_pwd = ft_split(pwd, '/');
		final_path = get_path_from_arrays(split_pwd, sanitized_arg_path);
		free_array(split_pwd, NULL);
	}
	return (final_path);
}
