/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:34:51 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/24 11:18:44 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*src_tmp;
	char	*dest_tmp;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	src_tmp = (char *)src;
	dest_tmp = (char *)dest;
	if (dest > src)
	{
		while (n --)
			dest_tmp[n] = src_tmp[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			dest_tmp[i] = src_tmp[i];
			i ++;
		}
	}
	return (dest_tmp);
}
/*int	main()
{
	char str1[] = "HeyHey";
	char str2[] = "*hello";
	char *ptr;
	size_t i = 0;
	size_t count = 4;

	ptr = (char *)malloc(100 * sizeof(char));
	ptr = ft_memmove(str1, str2, count);
	while (ptr[i] != '\0')
	{
		printf("%c \n", ptr[i]);
		i ++;
	}
	return(0);
}*/
