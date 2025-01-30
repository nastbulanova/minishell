/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:18:29 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/30 15:35:33 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
/*int main()
{
    const char str1[] = "HElloHello";
    int c = 111;
	size_t n = 4;
    char *ptr;

    ptr = ft_memchr(str1, c, n);
    if (ptr == NULL)
    {
        printf("Character not found\n");
        return (0);
    }
    printf("%c ", *ptr);
    return (0);
}*/
