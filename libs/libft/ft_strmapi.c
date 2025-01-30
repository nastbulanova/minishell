/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:34:36 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/26 11:09:57 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	str = (char *)malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
char    *ft_index(unsigned int i, char s)
{
    s = (char)i;
    return(&s);
}

int main() 
{
    const char str1[] = "HelloHello";
    char *ptr;
    size_t len = 5;
    size_t i;

    ptr = ft_strmapi(str1, ft_index);
    printf("Address %p\n", ptr);
    i = 0;
    while (i < len)
    {
        printf("%c ", ptr[i]);
        i ++;
    }
    return (0);
}
*/
