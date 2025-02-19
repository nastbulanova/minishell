/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:39:48 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/19 11:33:12 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Reads a line from input with heredoc prompt.
 *
 * Sets heredoc signal handlers and replaces the getc function,
 * then reads a line using readline(). Restores the original settings.
 *
 * @param data Pointer to the minishell data structure.
 * @param pipe_fd Array of pipe file descriptors.
 * @param line Pointer to store the read line.
 * @return OK on success or an error code.
 */
t_parser_error	get_line(t_minishell *data, int *pipe_fd, char **line)
{
	int		(*default_getc_function)(FILE *);

	set_state_signal_handlers(HERE_DOC);
	default_getc_function = rl_getc_function;
	rl_getc_function = getc;
	*line = readline(">");
	if (data->exit_code == 130)
	{
		if (close(pipe_fd[1]) == -1)
		{
			pipe_fd[1] = -1;
			return (CLOSE_FD_ERROR);
		}
		return (CTRLC);
	}
	rl_getc_function = default_getc_function;
	set_state_signal_handlers(MAIN);
	return (OK);
}

/**
 * @brief Processes the input line and writes it to a pipe.
 *
 * Calls get_line() to read a line, writes the line to the pipe,
 * frees the allocated memory, and closes the write end.
 *
 * @param data Pointer to the minishell data structure.
 * @param pipe_fd Array of pipe file descriptors.
 * @return OK on success or an error code.
 */
t_parser_error	process_line(t_minishell *data, int *pipe_fd)
{
	char	*line;
	int		error;

	line = NULL;
	error = OK;
	error = get_line(data, pipe_fd, &line);
	if (error == OK)
	{
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	else
	{
		if (close(pipe_fd[1]) == -1)
		{
			fprintf(stderr, "HIT process_line\n");
			return (CLOSE_FD_ERROR);
		}
		return (error);
	}
	if (close(pipe_fd[1]) == -1)
		return (CLOSE_FD_ERROR);
	return (OK);
}

/**
 * @brief Completes the heredoc input process.
 *
 * Creates a pipe, processes a line through process_line(), reads the output,
 * and closes the pipe's read end. Returns errors if any occur.
 *
 * @param data Pointer to the minishell data structure.
 * @param new_line Pointer to store the resulting line.
 * @return OK on success or an error code.
 */
t_parser_error	finish_line(t_minishell *data, char **new_line)
{
	t_parser_error	error;
	int				pipe_fd[2];

	error = OK;
	if (pipe(pipe_fd) == -1)
		return (PIPE_ERROR);
	error = process_line(data, pipe_fd);
	if (error == OK)
		*new_line = get_next_line(pipe_fd[0]);
	else
	{
		if (close(pipe_fd[0]) == -1)
		{
			fprintf(stderr, "HIT finish_line\n");
			return (CLOSE_FD_ERROR);
		}
		return (error);
	}
	if (!*new_line)
	{
		if (close(pipe_fd[0]) == -1)
		{
			fprintf(stderr, "HIT finish_line2\n");
			return (CLOSE_FD_ERROR);
		}
		return (MALLOC_ERROR);
	}
	if (close(pipe_fd[0]) == -1)
		return (CLOSE_FD_ERROR);
	return (OK);
}

/**
 * @brief Tokenizes an input string into a list of tokens.
 *
 * Iterates over the string, using check_char() to build tokens.
 * On success, appends the token list; on error, cleans up tokens.
 *
 * @param token_head Pointer to the head of the token list.
 * @param line The input string to tokenize.
 * @return OK on success or an error code.
 */
t_parser_error	tokenize_str(t_token **token_head, char *line)
{
	int				i;
	t_parser_error	error;
	t_token			*token;

	error = OK;
	token = NULL;
	i = 0;
	while (line[i] != '\0' && error == OK)
		error = check_char(&token, line, &i);
	if (error == OK)
		token_append(token_head, token);
	else
		token_clean(token);
	return (error);
}

/**
 * @brief Performs lexical analysis on the input line.
 *
 * Tokenizes the input line and handles heredoc continuation if the
 * last token is a pipe. Cleans up tokens and returns error codes if needed.
 *
 * @param data Pointer to the minishell data structure.
 * @param line The input string to analyze.
 * @return OK on success or an error code.
 */
t_parser_error	lexer(t_minishell *data, char *line)
{
	char			*new_line;
	t_parser_error	er;
	t_token			*tmp;

	er = OK;
	tmp = NULL;
	er = tokenize_str(&(data->token_head), line);
	if (er != OK)
		return (lexer_error((data->token_head), er));
	while (is_last_token_pipe(data->token_head))
	{
		er = finish_line(data, &new_line);
		if (er != OK)
			return (lexer_error((data->token_head), er));
		if (new_line)
		{
			er = tokenize_str(&(data->token_head), new_line);
			free(new_line);
			if (er != OK)
				return (token_clean(tmp), lexer_error((data->token_head), er));
		}
		else
			return (lexer_error(data->token_head, MALLOC_ERROR));
	}
	return (OK);
}
