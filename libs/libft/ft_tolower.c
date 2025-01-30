/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:47:00 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/24 12:03:02 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c = c + 32;
	return (c);
}
/*int main()
{
	int c[4] = {64, 70, 90, 97};
	int i = -1;

	while (i ++ < 3)
		printf("int %d, result %d\n", c[i], ft_tolower(c[i]));
	return(0);
}*/
