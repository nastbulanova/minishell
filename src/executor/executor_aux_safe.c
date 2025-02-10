/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux_safe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:23:26 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:23:28 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	close_fd(int *fd)
{
	if (fd && *fd >= 0)
	{
		if (close(*fd) == -1)
		{
			ft_putstr_fd("Failed to close file descriptor.\n", STDERR_FILENO);
			return (false);
		}
		*fd = -1;
		return (true);
	}
	return (true);
}

bool	close_pipe(int pipe_fd[2])
{
	return (close_fd(&pipe_fd[0]) && close_fd(&pipe_fd[1]));
}

bool	safe_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) != 0)
	{
		ft_putstr_fd("Failed to create pipe.\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

bool	safe_dup_two(int fd, int fd_two)
{
	if (dup2(fd, fd_two) == -1)
	{
		ft_putstr_fd("dup2 error.\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}
