/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 15:24:39 by akitsenk          #+#    #+#             */
/*   Updated: 2024/05/15 12:23:21 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	check_buf_nl(char *buf)
{
	size_t	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

void	move_buf(char *buf)
{
	size_t	i;
	size_t	j;
	int		flag;

	i = 0;
	j = 0;
	flag = 0;
	while (buf[i])
	{
		if (flag)
		{
			buf[j] = buf[i];
			j++;
		}
		if (buf[i] == '\n')
			flag = 1;
		buf[i] = '\0';
		i++;
	}
}

size_t	cnt_chr(char *next_line, char *buf)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (next_line)
	{
		while (next_line[i] != '\0')
			i++;
	}
	j = 0;
	while (buf[j] != '\0')
	{
		if (buf[j] == '\n')
			return (i + j + 1);
		j++;
	}
	return (i + j);
}

char	*crt_line(char *next_line, char *buf)
{
	char	*new_line;
	size_t	i;
	size_t	j;

	new_line = NULL;
	new_line = malloc(sizeof(char) * (cnt_chr(next_line, buf) + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (next_line && next_line[i] != '\0')
	{
		new_line[i] = next_line[i];
		i++;
	}
	free(next_line);
	j = 0;
	while (buf[j])
	{
		new_line[i++] = buf[j];
		if (buf[j] == '\n')
			break ;
		j++;
	}
	new_line[i] = '\0';
	return (new_line);
}
