/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:33:46 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/29 11:11:54 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	ch;

	ch = (unsigned char)c;
	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			return ((char *)(s + i));
		i ++;
	}
	if (c == '\0')
		return ((char *)(s + i));
	return (NULL);
}
/*int main()
{
    const char str1[] = "E";
    int c = 69;
    char *ptr;

    ptr = ft_strchr(str1, c);
    if (ptr == NULL)
    {
        printf("Character not found\n");
        return (0);
    }
    printf("%c ", *ptr);
    return (0);
}*/
