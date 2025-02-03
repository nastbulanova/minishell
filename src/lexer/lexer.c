#include "../../inc/minishell.h"

void    finish_line_child(char *prompt, int *pipe_fd)
{
	char	*line;

	line = NULL;
	close(pipe_fd[0]);
	line = readline(prompt);
	if (line)
	{
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

t_parser_error finish_line(char *prompt, char **new_line)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	status = 0;
	if (pipe(pipe_fd) == -1)
		return (PIPE_ERROR);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (FORK_ERROR);
	}
	if (pid == 0)
		finish_line_child(prompt, pipe_fd);
	waitpid(pid, &status, 0);
	close(pipe_fd[1]);
	*new_line = get_next_line(pipe_fd[0]);
	if (!*new_line)
		return (MALLOC_ERROR);
	close(pipe_fd[0]);
	return (OK);
}

t_parser_error	check_char(t_token **token_head, char *line, int *i)
{
	if (ft_iswordchar(line[*i]))
		return (while_sequence(token_head, line, ft_iswordchar, &i));
	else if (line[*i] == '\'')
		return (find_field(token_head, line, ft_isquote, &i));
	else if (line[*i] == '\"')
		return (find_field(token_head, line, ft_isdblquote, &i));
	else if (line[*i] == '>')
		return (find_redir(token_head, line, '>', &i));
	else if (line[*i] == '<')
		return (find_redir(token_head, line, '<', &i));
	else if (line[*i] == '|')
		return((*i)++, token_add(&token_head, &(line[(*i) - 1]), 1, PIPE));
	else
		(*i)++;
	return (OK);
}

int	is_last_token_pipe(t_token *head)
{
	t_token	*current;

	current = head;
	if (!current)
		return (0);
	while (current->next)
		current = current->next;
	return (current->type == PIPE);
}

t_parser_error	lexer(t_minishell *data, char *line)
{
	int				i;
	char			*new_line;
	t_parser_error	error;

	i = 0;
	error = OK;
	new_line = NULL;
	while (line[i] != '\0' && error == OK)
		error = check_char(&(data->token_head), line, &i);
	if (error != OK)
		return(lexer_error((data->token_head), error));
	if (is_last_token_pipe(data->token_head))
	{
		error = finish_line(data->prompt, &new_line);
		if (new_line && error == OK)
		{
			lexer(data, new_line);
			free(new_line);
		}
		else
			return (lexer_error(data->token_head, error), error);
	}
	return (OK);
}
