#include "../../inc/minishell.h"


t_parser_error list_path(t_env *env, char ***paths)
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

t_parser_error loop_path(char **paths, char *cmd, char ***cmd_with_path)
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

t_parser_error	find_path(t_env *env, char *cmd, char **cmd_with_path)
{
	char	**paths;

	if (!access(cmd, 0))
	{
		*cmd_with_path = ft_strdup(cmd);
		if (!cmd_with_path)
			return(MALLOC_ERROR);
		else
			return(OK);
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
