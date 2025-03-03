/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:23:56 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/03 11:26:33 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * @file pwd.c
 * @brief Implementation of the pwd builtin command for Minishell.
 */

/**
 * @brief Retrieves and prints the current working directory.
 *
 * This function uses `getcwd()` to obtain the absolute path of the 
 * current working directory. The path is printed to the specified 
 * file descriptor `fd`. If `fd` is invalid, it defaults to `STDOUT_FILENO`.
 *
 * @param fd The file descriptor where the output should be written.
 * @return Returns 0 on success, or 1 if an error occurs.
 *
 * @note If `getcwd()` fails, an error message is printed to STDERR.
 * @note The function ensures proper memory management by freeing 
 *       the dynamically allocated string returned by `getcwd()`.
 */
int	cmd_pwd(int fd)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	errno = 0;
	if (fd < 0)
		fd = STDOUT_FILENO;
	if (!pwd && errno != 0)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	if (!pwd && errno == 0)
	{
		ft_putstr_fd("\n", fd);
		return (1);
	}
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	free(pwd);
	return (0);
}
