/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:36:34 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/29 13:52:08 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	long			i;
	unsigned char	ch;

	ch = (unsigned char)c;
	if (!s)
		return (NULL);
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == ch)
		{
			return ((char *)&s[i]);
		}
		i --;
	}
	return (NULL);
}
/*int main()
{
    const char str1[] = "bonjour";
    int c = 'o';
    char *ptr;

    ptr = ft_strrchr(str1, c);
    if (ptr == NULL)
    {
        printf("Character not found\n");
        return (0);
    }
    printf("%c ", *ptr);
    return (0);
}*/
