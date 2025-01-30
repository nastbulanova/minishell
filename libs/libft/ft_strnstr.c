/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:34:48 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/24 13:10:30 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!haystack || !needle)
		return (NULL);
	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && needle[j] != '\0' && i < len)
	{
		j = 0;
		if (haystack[i] == needle[0])
		{
			while (haystack[i + j] == needle[j] && (i + j) < len)
			{
				if (needle[j + 1] == '\0')
					return ((char *)haystack + i);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

/*int main()
{
    const char str1[] = "HelloHello";
    const char str2[] = "ll";
    char *ptr;
    size_t size = 7;
    size_t len;
    size_t i;

    ptr = ft_strnstr(str1, str2, size);
    printf("Address %p\n", ptr);
    i = 0;
    len = ft_strlen(str2);
    while (i < len)
    {
        printf("%c", ptr[i]);
        i ++;
    }
    return (0);
}*/
