/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:27:20 by akitsenk          #+#    #+#             */
/*   Updated: 2024/05/03 10:43:02 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	t_size;

	if (count && size && count > (UINT_MAX / size))
		return (NULL);
	t_size = count * size;
	ptr = (void *)malloc(t_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, t_size);
	return (ptr);
}
/*int main()
{
    size_t count = 10;
    size_t size = 10;
    size_t i;
	char *ptr;

	ptr = ft_calloc(count, size);
    printf("Address %p\n", ptr);
    i = 0;
    while (i < size)
	{
        printf("%c ", ptr[i]);
		i ++;
	}
    return (0);
}*/
