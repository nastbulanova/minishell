/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:26:59 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/24 11:57:51 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	i;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	i = dstlen;
	while (i < (dstsize - 1) && src[i - dstlen])
	{
		dst[i] = src[i - dstlen];
		i++;
	}
	dst[i] = '\0';
	return (srclen + dstlen);
}
/*int	main()
{
	char str1[100] = "AAAAA";
	const char str2[] = "bbbbbb";	
	size_t count = 7;
	size_t i = 0;


	printf("My %d \n", (int)ft_strlcat(str1, str2, count));
	i = 0;
	while (str1[i] != '\0')
	{
		printf("%c", str1[i]);
		i ++;
	}
	printf("\n");
	return(0);
}*/
