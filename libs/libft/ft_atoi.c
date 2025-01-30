/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:27:09 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/24 14:49:26 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	size_t	i;
	int		nb;
	int		sign;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		nb = nb * 10 + (str[i] - 48);
		i++;
	}
	return (nb * sign);
}
/*int main()
{
    size_t i = 0;
    char str1[] = "  --234";
    char str2[] = "  -234a";
    char str3[] = "  -+23a4";
    char str4[] = "  -a234";
    char str5[] = "  +234";

    while (str1[i] != 0 )
    {
        printf("%c", str1[i]);
        i ++;
    }
    printf("\nOrig atoi %d \n", atoi(str1));
    printf("ft_atoi %d \n", ft_atoi(str1));
    
    i = 0;
    while (str2[i] != 0 )
    {
        printf("%c", str2[i]);
        i ++;
    }
    printf("\nOrig atoi %d \n", atoi(str2));
    printf("ft_atoi %d \n", ft_atoi(str2));


    i = 0;
    while (str3[i] != 0 )
    {
        printf("%c", str3[i]);
        i ++;
    }
    printf("\nOrig atoi %d \n", atoi(str3));
    printf("ft_atoi %d \n", ft_atoi(str3));

    i = 0;
    while (str4[i] != 0 )
    {
        printf("%c", str4[i]);
        i ++;
    }
    printf("\nOrig atoi %d \n", atoi(str4));
    printf("ft_atoi %d \n", ft_atoi(str4));

    i = 0;
    while (str5[i] != 0 )
    {
        printf("%c", str5[i]);
        i ++;
    }
    printf("\nOrig atoi %d \n", atoi(str5));
    printf("ft_atoi %d \n", ft_atoi(str5));
}*/
