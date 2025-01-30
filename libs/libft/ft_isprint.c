/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:15:07 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/24 10:54:11 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/*int main()
{
	int c[3] = {6, 32, 127};
	int i = -1;

	while (i ++ < 2)
		printf("int %d, result %d\n", c[i], ft_isprint(c[i]));
	return(0);
}*/
