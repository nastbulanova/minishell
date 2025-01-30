/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:33:58 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/26 11:14:19 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i ++;
	}
}
/*void	test(unsigned int i, char *st)
{
	st[i] = '*';
}

int main() 
{
    char str1[] = "HelloHello";
    size_t i;

    ft_striteri(str1, test);
    i = 0;
    while (str1[i] != '\0')
    {
        printf("%c ", str1[i]);
        i ++;
    }
    return (0);
}*/
