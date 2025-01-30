/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:32:58 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/25 18:01:35 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*int main()
{
	char	*ptr;
	size_t i = 0;
	size_t	n = 10;

	ptr = (char *)malloc(n * sizeof(char));
	ft_bzero(ptr, n);
	while (i < n)
	{
		printf("%c ", ptr[i]);
		i ++;
	}
}*/
