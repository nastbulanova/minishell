/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:48:08 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/29 11:40:16 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wrdcnt(const char *s, char c)
{
	size_t	i;
	int		count;
	int		flag;

	count = 0;
	flag = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			count ++;
		}
		else if (s[i] == c)
			flag = 0;
		i ++;
	}
	return (count);
}

static void	ft_wrdcln(char **wrds, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		free(wrds[i]);
		wrds[i] = NULL;
		i ++;
	}
	free(wrds);
}

static int	ft_wrdcrt(char **wrds, char const *s, char c, size_t chrcnt)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			chrcnt ++;
		else if (chrcnt > 0)
		{
			wrds[j++] = ft_substr(s, i - chrcnt, chrcnt);
			if (!wrds[j - 1])
			{
				ft_wrdcln(wrds, j - 1);
				return (0);
			}
			chrcnt = 0;
		}
		i ++;
	}
	if (chrcnt > 0)
		wrds[j++] = ft_substr(s, i - chrcnt, chrcnt);
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char			**wrds;
	int				flag;
	int				wrdcnt;
	unsigned char	ch;
	size_t			chrcnt;

	chrcnt = 0;
	ch = (unsigned char)c;
	if (!s)
		return (NULL);
	wrdcnt = ft_wrdcnt(s, ch);
	wrds = malloc((wrdcnt + 1) * sizeof(char *));
	if (wrdcnt == 0)
	{
		wrds[0] = NULL;
		return (wrds);
	}
	if (!wrds)
		return (NULL);
	flag = ft_wrdcrt(wrds, s, ch, chrcnt);
	if (flag == 0)
		return (NULL);
	else
		wrds[flag ++] = NULL;
	return (wrds);
}
/*int main()
{
    const char str1[] = "ll*Hello*Hello*ll";
    char str2 = '*';
    char **ptr;
    size_t i;
    size_t j;
	size_t count = ft_wrdcnt(str1, str2);

    ptr = ft_split(str1, str2);
    printf("Address %p\n", ptr);
	i = 0;
	while (i < count)
	{
		j = 0;
		while (ptr[i][j] != '\0')
		{
			printf("%c", ptr[i][j]);
			j ++;
		}
		printf("\n");
		i ++;
	}
    return (0);
}*/
