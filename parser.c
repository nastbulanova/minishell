#include "minishell.h"

t_exec_data	*exec_data_init()
{
	t_exec_data	*exec_data;

	exec_data = (t_exec_data *)malloc(sizeof(t_exec_data));
	if (!exec_data)
		return(NULL);////////////////////////error_func

	return(exec_data);	
}

void	group_init(t_token  **token_head)
{
	int		group;
	t_token	*current;

	group = 0;
	current = *token_head;
	while (current)
	{
		if (current->prev)
		{
			if (current->prev->prev)
			{
				if (current->prev->prev->type >= 5 && current->prev->prev->type <= 9)
					group++;
			}
		}
		current->group = group;
		current = current->next;
	}
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

t_exec_data	*cmd_check(t_token *token, char **env)
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
		err_msg("command not found:", cmd);/////////////////////////////////////new prompt
	free(cmd);
	return(cmd_with_path);
}

void	check_context(t_minishell *data, t_token **token, int *i)
{
	if (!(*token)->next)///////////////////////what about next group?
		do_cmd(data->exec_data);//////////////////piping, redir, execve
	else if ((*token)->next->group > (*token)->group)
	{
		do_cmd(data->exec_data);//////////////////piping, redir, execve
		(*token) = (*token)->next;
		*i = 0;
	}
	else
	{
		(*token) = (*token)->next;
		(*i)++;
	}
}

char	*open_field(t_minishell *data, t_token *token)
{
	int		i;
	int		j;
	char	*str;
	char	*name;
	char	*result;
	int		start;
	char	*var_value;

	i = 0;
	str = token->start;
	result = "";
	var_value = NULL;
	start = 0;
	while (i < token->len)
	{
		if (str[i] == '$')//////////////////        $? can be here? - will be added
		{
			j = i + 1;
			while (str[j] != ' ')
				j++;
			name = ft_substr(str, i + 1, j - i);
			var_value = env_var_replace(data, name);
			if (var_value)
				result = ft_strjoin(result, ft_strjoin(ft_substr(str, start, i), var_value));
			else
				result = ft_strjoin(result, ft_substr(str, start, i));
			i = j + 1;
			start = i;
			free(var_value);
			free(name);
		}
		else
			i++;
	}
	if (ft_strlen(result) == 0)
		return(ft_substr(token->start, 0, token->len));
	else
		return(ft_strjoin(result, ft_substr(str, j + 1, i)))
}

char	*env_var_replace(t_minishell *data, char *name)
{
	char	*tmp;
	int		i;
	int		len;

	i = -1;
	name = ft_strjoin(name, '=');
	len = ft_strlen(name);
	while (data->env[++i])
	{
		if (!ft_strcmp(data->env[i], name, len))
			return(ft_strnstr(data->env[i], name, len));
	}
	return (NULL);
}

int	opt_count(t_token *token)
{
	t_token	*tmp;
	int		count;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (!(tmp->type >= 1 && tmp->type <= 4))
			break ;
		count++;
		tmp = tmp->next;
	}
	return (count);
}

void	opt_check(t_minishell *data, t_token *token)
{
	t_token	*tmp;
	int		count;
	int		i;

	tmp = token;
	count = opt_count(token);
	data->exec_data->opt = (char **)malloc((count + 1) * sizeof(char *));
	//if (!data->exec_data->opt)
	///////////////////////////////////////////////////////////////////////	error
	i = 0;
	while (i < count)
	{
		if (tmp->type == 1)
			data->exec_data->opt[i] = ft_substr(token->start, 0, token->len);
		else if (tmp->type == 2)
			data->exec_data->opt[i] = env_var_replace();///////////////////////////// handle env_var
		else if (tmp->type == 3)
			data->exec_data->opt[i] = ft_substr(token->start, 0, token->len);
		else
			data->exec_data->opt[i] = open_field(data, token);
		token = token->next;
		i++;
	}
}

int	parser(t_minishell *data)
{
	t_exec_data	*exec_data;
	t_token		*token;
	int			i;

	data->exec_data = exec_data_init();
	group_init(&(data)->token_head);
	print_token(data->token_head);/////////////////////////
	token = data->token_head;
	i = 0;
	while (token)
	{
		if (i == 0)
		{
			if (token->type == 1)
			{
				exec_data->cmd = cmd_check(token, data->env);
				check_context(data, &token, &i);///////
			}
			else
				error();/////////////////////////////////////////////////////////new prompt
		}
		if (i == 1)
		{
			if (token->type >= 1 && token->type <= 4)
			{
				//while 
				//opt & args until another token->type to char**
				check_context(data, &token, &i);
			}
			else if (token->type == 5)
			{
				/* find a filename, put to struct new_outfile */
				check_context(data, &token, &i);
			}
			else if (token->type == 6)
			{
				/* find a filename, put to struct infile*/
				check_context(data, &token, &i);
			}
			else if (token->type == 7)
			{
				/* find a filename, put to struct exist_outfile*/
				check_context(data, &token, &i);
			}
			else if (token->type == 8)
			{
				/* find a filename, put to struct here_doc*/
				check_context(data, &token, &i);
			}
			else if (token->type == 9)
			{
				/* put to struct is_pipe*/
				check_context(data, &token, &i);
			}

		}
		if (i == 2)
		{
			if (token->type == 5)
			{
				/* find a filename, put to struct new_outfile */
				check_context(data, &token, &i);
			}
			else if (token->type == 6)
			{
				/* find a filename, put to struct infile*/
				check_context(data, &token, &i);
			}
			else if (token->type == 7)
			{
				/* find a filename, put to struct exist_outfile*/
				check_context(data, &token, &i);
			}
			else if (token->type == 8)
			{
				/* find a filename, put to struct here_doc*/
				check_context(data, &token, &i);
			}
			else if (token->type == 9)
			{
				/* put to struct is_pipe*/
				check_context(data, &token, &i);
			}
		}

	}

	return (0);
}
