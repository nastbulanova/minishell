/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:57:52 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/03 18:43:57 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

char	*built_exit_string(const char *str)
{
	char	template[46];
	char	*result;
	size_t	template_index;
	size_t	str_index;

	ft_strlcpy(template, "minishell: exit: : numeric argument required\n", 46);
	result = safe_malloc(ft_strlen(str) + 46);
	template_index = -1;
	str_index = -1;
	while (++template_index < 17)
		result[template_index] = template[template_index];
	while (++str_index < ft_strlen(str))
		result[template_index + str_index] = str[str_index];
	while (template_index + str_index < (ft_strlen(str) + 46))
	{
		result[template_index + str_index] = template[template_index];
		template_index++;
	}
	return (result);
}

static void	check_sign(const char *str, int *index, int *sign)
{
	*sign = 1;
	*index = 0;
	if (str[*index] == '-' || str[*index] == '+')
	{
		if (str[*index] == '-')
			*sign = -1;
		(*index)++;
	}
}

static void	ft_exit_atoi_aux(char *str, int stdin_backup, int stdout_backup)
{
	close_fd(&stdin_backup);
	close_fd(&stdout_backup);
	minishell_exit(built_exit_string(str), 2, STDERR_FILENO, true);
}

char	ft_exit_atoi(char *str, int stdin_backup, int stdout_backup)
{
	int			sign;
	int			digit;
	int			index;
	long long	value;

	check_sign(str, &index, &sign);
	value = 0;
	while (ft_isdigit(str[index]))
	{
		digit = str[index] - '0';
		if (sign < 0 && (INT64_MAX - (value * 10) < digit - 1))
		{
			ft_exit_atoi_aux(str, stdin_backup, stdout_backup);
			return (2);
		}
		else if (sign > 0 && (INT64_MAX - (value * 10) < digit))
		{
			ft_exit_atoi_aux(str, stdin_backup, stdout_backup);
			return (2);
		}
		value = (value * 10) + (digit);
		index++;
	}
	value = value * sign;
	return ((unsigned char)value);
}
