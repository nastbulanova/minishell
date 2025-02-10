/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:24:26 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:46:33 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**get_flags_null(void)
{
	static char	*flags[] = {NULL};

	return (flags);
}

char	**get_flags_cd(void)
{
	static char	*flags[] = {"L", "P", NULL};

	return (flags);
}

char	**get_flags_echo(void)
{
	static char	*flags[] = {"n", "e", "E", NULL};

	return (flags);
}

char	**get_flags_export(void)
{
	static char	*flags[] = {"p", NULL};

	return (flags);
}

char	**get_flags_unset(void)
{
	static char	*flags[] = {"v", "f", NULL};

	return (flags);
}
