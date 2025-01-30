/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:37:01 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/26 11:07:00 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	long	i;
	long	j;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) && i <= j)
		i ++;
	if (i > j)
		return (ft_strdup(s1 + j + 1));
	while (ft_strchr(set, s1[j]) && j >= 0)
		j --;
	str = malloc(j - i + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[i], j - i + 2);
	return (str);
}
/*int main()
{
    const char str1[] = "   xxxtripouille   xxx";
    const char str2[] = " x";
    char *ptr;
    size_t len;
    size_t i;

    ptr = ft_strtrim(str1, str2);
    printf("Address %p\n", ptr);
    i = 0;
    len = ft_strlen(ptr);
    while (i < len)
    {
        printf("%c", ptr[i]);
        i ++;
    }
    return (0);
}*/
