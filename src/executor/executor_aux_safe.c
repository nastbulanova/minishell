/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_aux_safe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:23:26 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/11 18:14:40 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * @file executor_aux_safe.c
 * @brief Utility functions for safely handling file descriptors and pipes 
 * in the executor.
 */

/**
 * @brief Safely closes a file descriptor.
 *
 * This function checks if the given file descriptor is valid (non-negative) 
 * before attempting
 * to close it. If the closure fails, an error message is printed to 
 * standard error.
 *
 * @param fd Pointer to the file descriptor to be closed.
 * @return true if the file descriptor was successfully closed or was 
 * already invalid,
 *         false if the closure failed.
 */
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

/**
 * @brief Closes both ends of a pipe.
 *
 * This function uses close_fd to safely close both read and write ends 
 * of a pipe.
 *
 * @param pipe_fd An array containing two file descriptors representing 
 * the pipe.
 * @return true if both ends were successfully closed, false if either 
 * failed.
 */
bool	close_pipe(int pipe_fd[2])
{
	return (close_fd(&pipe_fd[0]) && close_fd(&pipe_fd[1]));
}

/**
 * @brief Creates a pipe safely.
 *
 * This function attempts to create a pipe and prints an error message if
 *  it fails.
 *
 * @param pipe_fd An array that will hold the file descriptors for the pipe.
 * @return true if the pipe was successfully created, false otherwise.
 */
bool	safe_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) != 0)
	{
		ft_putstr_fd("Failed to create pipe.\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}

/**
 * @brief Duplicates a file descriptor safely.
 *
 * This function uses dup2 to duplicate a file descriptor and prints an 
 * error message if it fails.
 *
 * @param fd The original file descriptor.
 * @param fd_two The target file descriptor.
 * @return true if duplication was successful, false otherwise.
 */
bool	safe_dup_two(int fd, int fd_two)
{
	if (dup2(fd, fd_two) == -1)
	{
		ft_putstr_fd("dup2 error.\n", STDERR_FILENO);
		return (false);
	}
	return (true);
}
