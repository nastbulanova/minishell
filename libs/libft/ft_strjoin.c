/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:34:13 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/30 15:37:51 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s_join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s_join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s_join)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s_join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		s_join[i] = s2[j];
		i ++;
		j ++;
	}
	s_join[i] = '\0';
	return (s_join);
}
/*int main()
{
    const char str1[] = "Hello";
    const char str2[] = "lol";
    char *ptr;
    size_t i;

    ptr = ft_strjoin(str1, str2);
    printf("Address %p\n", ptr);
    i = 0;
    while (ptr[i] != '\0')
    {
        printf("%c", ptr[i]);
        i ++;
    }
    return (0);
}*/
