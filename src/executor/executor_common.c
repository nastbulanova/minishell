/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_common.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:17:42 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:17:47 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	has_heredoc(t_redir *redir)
{
	if (!redir)
		return (false);
	while (redir)
	{
		if (redir->type == HEREDOC || redir->type == HEREDOC_QUOTED)
			return (true);
		redir = redir->next;
	}
	return (false);
}

bool	has_input(t_redir *redir)
{
	if (!redir)
		return (false);
	while (redir)
	{
		if (redir->type == INPUT || redir->type == HEREDOC
			|| redir->type == HEREDOC_QUOTED)
			return (true);
		redir = redir->next;
	}
	return (false);
}

bool	has_output(t_redir *redir)
{
	if (!redir)
		return (false);
	while (redir)
	{
		if (redir->type == OUTPUT || redir->type == OUTPUT_APPEND)
			return (true);
		redir = redir->next;
	}
	return (false);
}

char	*get_rdir_error(t_redir *redir)
{
	if (!redir)
		return (NULL);
	while (redir)
	{
		if (redir->error)
			return (redir->error);
		redir = redir->next;
	}
	return (NULL);
}

void	init_cmd(t_exec_data *exec_data)
{
	exec_data->cmd = NULL;
	exec_data->opt = NULL;
	exec_data->is_builtin = false;
	exec_data->redirs = NULL;
	exec_data->exit_status = 0;
	exec_data->input_fd = -1;
	exec_data->output_fd = -1;
	exec_data->outpipe[0] = -1;
	exec_data->outpipe[1] = -1;
}
