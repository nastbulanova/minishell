/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao <joao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:41:16 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/14 14:23:51 by joao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Checks if the command is a built-in.
 *
 * Splits the built-in commands and compares them with cmd.
 * If a match is found, duplicates cmd and sets the is_builtin flag.
 * 
 * @param data Triple pointer to minishell data.
 * @param cmd Command string.
 * @param cmd_with_path Pointer to store the command with path.
 * @return OK on success or MALLOC_ERROR.
 */
static t_parser_error	is_builtin(t_minishell ***data, char *cmd,
char **cmd_with_path)
{
	char	**builtin;
	size_t	len;
	int		i;

	len = ft_strlen(cmd) + 1;
	builtin = ft_split(CONST_BUILTIN, ' ');
	if (!builtin)
		return (MALLOC_ERROR);
	i = -1;
	while (builtin[++i])
	{
		if (!ft_strncmp(cmd, builtin[i], len))
		{
			*cmd_with_path = ft_strdup(cmd);
			(**data)->exec_data->is_builtin = 1;
			free_array(builtin, NULL);
			if (!(*cmd_with_path))
				return (MALLOC_ERROR);
			else
				return (OK);
		}
	}
	free_array(builtin, NULL);
	return (OK);
}

/**
 * @brief Checks and processes the command.
 *
 * Validates cmd and checks if it is built-in; if not, finds its path or
 * duplicates it.
 * Updates exec_data->cmd and sets the int_cmd flag.
 * 
 * @param data Pointer to minishell data.
 * @param cmd Command string.
 * @param int_cmd Double pointer to an integer flag.
 * @return OK on success or MALLOC_ERROR.
 */
t_parser_error	cmd_check(t_minishell **data, char *cmd, int **int_cmd)
{
	char	*cmd_with_path;

	if (ft_strlen(cmd) == 0)
		return (**int_cmd = 0, OK);
	if (!cmd)
		return (MALLOC_ERROR);
	cmd_with_path = NULL;
	if (is_builtin(&data, cmd, &cmd_with_path) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (cmd_with_path)
		return ((*data)->exec_data->cmd = cmd_with_path, **int_cmd = 1, OK);
	if (find_path((*data)->env, cmd, &cmd_with_path) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (!cmd_with_path)
		cmd_with_path = ft_strdup(cmd);
	if (!cmd_with_path)
		return (MALLOC_ERROR);
	return ((*data)->exec_data->cmd = cmd_with_path, **int_cmd = 1, OK);
}
