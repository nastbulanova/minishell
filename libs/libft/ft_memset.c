/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:08:00 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/25 20:40:47 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i ++;
	}
	return (s);
}
/*int main()
{
	char	*ptr;
	int	c = 65;
	size_t i = 0;
	unsigned long	n = 10;

	ptr = (char *)malloc(n * sizeof(char));
	ptr = ft_memset(ptr, c, n);
	while (i < n)
	{
		printf("%c ", ptr[i]);
		i ++;
	}
}*/
