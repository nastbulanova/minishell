/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:17:29 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/03 10:54:16 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * @brief Checks if the given redirection is the last heredoc in the list.
 * 
 * @param redir Pointer to the current redirection node.
 * @return true if it is the last heredoc, false otherwise.
 */
static bool	is_last_heredoc(t_redir *redir)
{
	if (!redir)
		return (true);
	while (redir)
	{
		if (redir->type == HEREDOC || redir->type == HEREDOC_QUOTED)
			return (false);
		redir = redir->next;
	}
	return (true);
}

static void	write_string(char *input, int fd)
{
	write(fd, input, strlen(input));
	write(fd, "\n", 1);
}

void	heredoc_write(t_redir *current, char *input, int fd)
{
	char		*p;
	t_minishell	*data;
	char		*temp;

	temp = NULL;
	if (current->type != HEREDOC_QUOTED)
	{
		data = get_shell(false);
		p = ft_strchr(input, '$');
		if (p && *(p + 1) != '\0')
		{
			temp = first_line_exp(data, input);
			write_string(input, fd);
			free(temp);
		}
		else
			write_string(input, fd);
	}
	else
		write_string(input, fd);
}

/**
 * @brief Determines if the heredoc input loop should terminate.
 * 
 * @param current Pointer to the current heredoc redirection node.
 * @param input The user-provided input string.
 * @param last_input Indicates whether this is the last heredoc input 
 * to be processed.
 * @param fd The file descriptor where heredoc content is written.
 * @return true if the loop should break, false otherwise.
 */
static bool	break_loop(t_redir *current, char *input, bool last_input, int fd)
{
	if (!input)
	{
		if (current->str && current->str[0] == '\0')
			return (true);
		if (last_input)
			write(fd, "\n", 1);
		return (true);
	}
	if (c_strcmp(input, current->str) == 0)
		return (true);
	if (last_input)
		heredoc_write(current, input, fd);
	return (false);
}

/**
 * @brief Handles the input loop for processing heredoc redirections.
 * 
 * Reads user input line by line, checking against the expected delimiter,
 * and writes to the provided file descriptor if necessary.
 * 
 * @param current Pointer to the current heredoc redirection node.
 * @param fd The file descriptor where heredoc content should be written.
 */
void	heredoc_loop(t_redir *current, int fd)
{
	char	*input;
	bool	last_input;
	int		(*default_getc_function)(FILE *);

	if (!current)
		return ;
	last_input = is_last_heredoc(current->next);
	set_state_signal_handlers(HERE_DOC);
	default_getc_function = rl_getc_function;
	rl_getc_function = getc;
	while (true)
	{
		input = readline("> ");
		if (break_loop(current, input, last_input, fd))
			break ;
		free(input);
	}
	if (input)
		free(input);
	rl_getc_function = default_getc_function;
	set_state_signal_handlers(MAIN);
}
