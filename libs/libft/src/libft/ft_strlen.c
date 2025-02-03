/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:40:43 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/03 13:25:29 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/**
 * @brief Calculates the length of a null-terminated
 string.
 *
 * This function calculates the length of the
 null-terminated string 's'.
 * The length is determined by counting the number
 of characters in 's'
 * until the null terminator ('\0') is encountered.
 *
 * @param s Pointer to the null-terminated string.
 * @return The length of the string 's' excluding
 the null terminator.
 *
 * @remark The function correctly handles null
 pointers, returning 0
 *         if 's' is NULL.
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
