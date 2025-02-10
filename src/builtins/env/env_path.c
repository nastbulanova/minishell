/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:29:15 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 14:29:36 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

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

char	*get_path_from_arrays(char **split_pwd, char **split_arg)
{
	char	*result;

	result = safe_malloc((get_arrays_size(split_pwd, split_arg) + 1)
			* sizeof(char));
	copy_arrays(result, split_pwd, split_arg);
	return (result);
}

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
