#include "minishell.h"

t_parser_error	is_builtin(t_minishell ***data, char *cmd, char **cmd_with_path)
{
	char	**builtin;
	size_t	len;
	int		i;

	len = ft_strlen(cmd) + 1;
	builtin = ft_split(CONST_BUILTIN, ' ');
	if (!builtin)
		return(MALLOC_ERROR);
	i = -1;
	while (builtin[++i])
	{
		if (!ft_strncmp(cmd, builtin[i], len))
		{
			*cmd_with_path = ft_strdup(cmd);
			(**data)->exec_data->is_builtin = 1;
			free_list(builtin);
			if (!(*cmd_with_path))
				return(MALLOC_ERROR);
			else
				return(OK);
		}
	}
	free_list(builtin);
	return(OK);
}

t_parser_error cmd_check(t_minishell **data, char *cmd, int **int_cmd)
{
	char	*cmd_with_path;

	if (ft_strlen(cmd) == 0)
		return (**int_cmd = 1, OK);
	if (!cmd)
		return(MALLOC_ERROR);
	cmd_with_path = NULL;
	if (is_builtin(&data, cmd, &cmd_with_path) == MALLOC_ERROR)
		return(MALLOC_ERROR);
	if (cmd_with_path)
		return ((*data)->exec_data->cmd = cmd_with_path, **int_cmd = 1, OK);
	if (find_path((*data)->env, cmd, &cmd_with_path) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (!cmd_with_path)
		cmd_with_path = ft_strdup(cmd);
	if (!cmd_with_path)
		return(MALLOC_ERROR);
	return((*data)->exec_data->cmd = cmd_with_path, **int_cmd = 1, OK);
}
