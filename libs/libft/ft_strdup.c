/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:33:52 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/24 15:32:00 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*int main()
{
    const char str1[] = "Hello";
    char *ptr;
    size_t i;

    ptr = ft_strdup(str1);
    printf("Address %p\n", ptr);
    i = 0;
    while (ptr[i] != '\0')
    {
        printf("%c", ptr[i]);
        i ++;
    }
    return (0);
}*/
