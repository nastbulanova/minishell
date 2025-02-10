/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:23:56 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:23:58 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmd_pwd(int fd)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	errno = 0;
	if (fd < 0)
		fd = STDOUT_FILENO;
	if (!pwd)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (1);
	}
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	free(pwd);
	return (0);
}
