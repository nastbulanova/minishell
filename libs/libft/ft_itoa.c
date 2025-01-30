/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:27:52 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/30 15:58:43 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_nblen(int nbr)
{
	long		len;
	long long	n;

	n = (long long)nbr;
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len ++;
		n = -n;
	}
	while (n >= 1)
	{
		n = n / 10;
		len ++;
	}
	return (len);
}

static char	*ft_nbtostr(int nbr, char *s, long len)
{
	long		i;
	long long	n;

	n = (long long)nbr;
	i = 0;
	if (n < 0)
	{
		s[i] = '-';
		n = -n;
		i ++;
	}
	s[len] = '\0';
	len --;
	while (len >= i)
	{
		s[len] = (n % 10) + '0';
		n = n / 10;
		len --;
	}
	return (s);
}

char	*ft_itoa(int n)
{
	long	nlen;
	char	*s;

	nlen = ft_nblen(n);
	s = (char *)malloc((nlen + 1) * sizeof(char));
	if (!s)
		return (NULL);
	if (n == 0)
	{
		s[0] = '0';
		s[1] = '\0';
	}
	else
		s = ft_nbtostr(n, s, nlen);
	return (s);
}
/*int main()
{
    int     n[7] = {-2147483648, -1000, -1, 0, 1, 1000, 2147483647};
    char    *s[6];
    size_t  i;
    size_t  j;

    i = 0;
    while(i <= 6)
    {
        printf("n= %d\n", n[i]);
        s[i] = ft_itoa(n[i]);
        printf("itoa ");
        j = 0;
        while (s[i][j] != 0 )
        {
            printf("%c", s[i][j]);
            j ++;
        }
        printf("\n");
        i ++;
    }
}*/
