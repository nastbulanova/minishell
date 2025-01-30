/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:42:03 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/25 20:22:12 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = 0;
	if (size > 0)
	{
		while ((src[i] != '\0') && (i < size - 1))
		{
			dst[i] = src[i];
			i ++;
		}
		dst[i] = '\0';
	}
	i = 0;
	while (src[i] != '\0')
		i ++;
	return (i);
}
/*int	main()
{
	char str[] = "Hello";
	char putstr[10];
	int len = 2;

	printf("%d\n",ft_strlcpy(putstr, str, len));
	printf("%s\n", putstr);
	return (0);
}*/
