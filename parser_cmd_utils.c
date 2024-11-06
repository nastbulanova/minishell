#include "minishell.h"

void	free_list(char **list)
{
	size_t	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i ++;
	}
	free(list);
}

char	**list_path(char **env)
{
	char	*tmp;
	char	**list;
	int		i;

	i = -1;
	list = NULL;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			tmp = ft_strnstr(env[i], "PATH=", 5);
			list = ft_split(tmp, ':');
			if (!list)
				return (NULL);
			break ;
		}
	}
	return (list);
}

char	*find_path(char **env, char *cmd)
{
	char	*tmp1;
	char	*tmp2;
	char	**paths;
	int		i;

	paths = list_path(env);
	i = -1;
	while (paths[++i])
	{
		tmp1 = ft_strjoin(paths[i], "/");
		tmp2 = ft_strjoin(tmp1, cmd);
		if (!access(tmp2, 0))
		{
			free(tmp1);
			free_list(paths);
			return (tmp2);
		}
		free(tmp1);
		free(tmp2);
	}
	free_list(paths);
	return (NULL);
}

char	*cmd_check(t_token *token, char **env)
{
	char	*cmd;
	char	*cmd_with_path;

	//////////////////////////////////////////////////////// here will be builtin handling
	cmd = ft_substr(token->start, 0, token->len);
	if (!access(cmd, 0))
		return(cmd);
	else if (!(*env))
		cmd_with_path = ft_strjoin("/usr/bin/", cmd);
	else
		cmd_with_path = find_path(env, cmd);
	if (!cmd_with_path)
		//err_msg("command not found:", cmd);/////////////////////////////////////new prompt
		printf("cmd not found");//////////////////////////////////////////////////////to delete
	free(cmd);
	return(cmd_with_path);
}