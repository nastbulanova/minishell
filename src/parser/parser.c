#include "../../inc/minishell.h"

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
void	opt_check(t_minishell *data, t_token *token)
{
	t_token	*tmp;
	int		count;
	int		i;

	tmp = token;
	count = 0;
	while (tmp)
	{
		if (!(tmp->type == 1 || tmp->type == 3 || tmp->type == 4))
			break ;
		count++;
		tmp = tmp->next;
	}
	data->exec_data->opt = (char **)malloc((count + 1) * sizeof(char *));
	//if (!data->exec_data->opt)
	///////////////////////////////////////////////////////////////////////	error
	tmp = token;
	i = 0;
	while (i < count)
	{
		data->exec_data->opt[i] = ft_substr(token->start, 0, token->len);
		token = token->next;
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
	while (token)/// add something for spaces
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
			if (token->type == 1 || token->type == 3 || token->type == 4)
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