/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:47:43 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/13 17:44:56 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Retrieves the PATH variable and splits it.
 *
 * Searches the environment list for "PATH" and splits its value by ':'.
 * 
 * @param env Pointer to the environment list.
 * @param paths Pointer to store the resulting array of path strings.
 * @return OK on success, MALLOC_ERROR on failure.
 */
t_parser_error	list_path(t_env *env, char ***paths)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!ft_strncmp(current->name, "PATH", 5))
		{
			*paths = ft_split(current->value, ':');
			if (!paths)
				return (MALLOC_ERROR);
			break ;
		}
		current = current->next;
	}
	return (OK);
}

/**
 * @brief Loops through paths to find the command's full path.
 *
 * Iterates over the array of paths, concatenates each with '/' and the command,
 * and checks for its accessibility.
 *
 * @param paths Array of directory paths.
 * @param cmd The command to locate.
 * @param cmd_with_path Pointer to store the command's full path.
 * @return OK on success, MALLOC_ERROR on failure.
 */
t_parser_error	loop_path(char **paths, char *cmd, char ***cmd_with_path)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = -1;
	while (paths[++i])
	{
		tmp1 = ft_strjoin(paths[i], "/");
		if (!tmp1)
			return (MALLOC_ERROR);
		tmp2 = ft_strjoin(tmp1, cmd);
		if (!tmp2)
			return (free(tmp1), MALLOC_ERROR);
		if (!access(tmp2, 0))
		{
			**cmd_with_path = tmp2;
			return (free(tmp1), OK);
		}
		free(tmp1);
		free(tmp2);
	}
	return (OK);
}

/**
 * @brief Finds the full path of a command.
 *
 * Checks direct accessibility of the command or uses the PATH environment
 * variable to locate it, returning the full path.
 *
 * @param env Environment list.
 * @param cmd The command to search for.
 * @param cmd_with_path Pointer to store the resulting full path.
 * @return OK on success, MALLOC_ERROR on failure.
 */
t_parser_error	find_path(t_env *env, char *cmd, char **cmd_with_path)
{
	char	**paths;

	if (ft_strchr(cmd, '/') && !access(cmd, 0))
	{
		*cmd_with_path = ft_strdup(cmd);
		if (!cmd_with_path)
			return (MALLOC_ERROR);
		else
			return (OK);
	}
	paths = NULL;
	if (env)
	{
		if (list_path(env, &paths) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	if (!paths)
	{
		paths = ft_split(CONST_PATH, ':');
		if (!paths)
			return (MALLOC_ERROR);
	}
	if (loop_path(paths, cmd, &cmd_with_path) == MALLOC_ERROR)
		return (free_array(paths, NULL), MALLOC_ERROR);
	return (free_array(paths, NULL), OK);
}
