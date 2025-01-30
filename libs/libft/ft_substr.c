/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:37:10 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/30 15:56:55 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;
	size_t	i;
	size_t	j;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	newstr = (char *)malloc(len + 1);
	if (!newstr)
		return (NULL);
	i = start;
	j = 0;
	while (i < slen && j < len)
		newstr[j++] = s[i++];
	newstr[j] = '\0';
	return (newstr);
}
/*int main()
{
    const char str1[] = "HelloHello";
    char *ptr;
    size_t size = 7;
    size_t start = 2;
    size_t len = 5;
    size_t i;

    ptr = ft_substr(str1, start, size);
    printf("Address %p\n", ptr);
    i = 0;
    while (i < len)
    {
        printf("%c", ptr[i]);
        i ++;
    }
    return (0);
}*/
