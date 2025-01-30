/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:22:57 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/24 12:05:51 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c = c - 32;
	return (c);
}
/*int main()
{
	int c[4] = {64, 97, 122, 123};
	int i = -1;

	while (i ++ < 3)
		printf("int %d, result %d\n", c[i], ft_toupper(c[i]));
	return(0);
}*/
