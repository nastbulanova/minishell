/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:33:15 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/24 16:42:49 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*int main() 
{
    char str1[] = "HelloHello";
    int fd = 2;
    size_t i;

    i = 0;
    while(str1[i] != '\0')
    {
        ft_putchar_fd(str1[i], fd);
        i ++;
    }
    return (0);
}*/
