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

char	*is_builtin(t_token *token)
{
	char	*cmd;
	if (!ft_strncmp(token->start, "echo", token->len))
		cmd = ft_strdup("echo");
	else if (!ft_strncmp(token->start, "cd", token->len))
		cmd = ft_strdup("cd");
	else if (!ft_strncmp(token->start, "pwd", token->len))
		cmd = ft_strdup("pwd");
	else if (!ft_strncmp(token->start, "export", token->len))
		cmd = ft_strdup("export");
	else if (!ft_strncmp(token->start, "unset", token->len))
		cmd = ft_strdup("unset");
	else if (!ft_strncmp(token->start, "env", token->len))
		cmd = ft_strdup("env");
	else if (!ft_strncmp(token->start, "exit", token->len))
		cmd = ft_strdup("exit");
	else
		return(NULL);
	//if (!cmd)
	//error
	//else
	//return(cmd);
}

char	*cmd_check(t_token *token, char **env)
{
	char	*cmd;
	char	*cmd_with_path;

	cmd = is_builtin(token);
	if (cmd)
		return (cmd);
	cmd = ft_substr(token->start, 0, token->len);
	//if (!cmd)
	//error
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
