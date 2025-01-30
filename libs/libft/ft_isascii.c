/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:15:07 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/24 10:56:44 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*int main()
{
	int c[3] = {-9, 127, 128};
	int i = -1;

	while (i ++ < 2)
		printf("int %d, result %d\n", c[i], ft_isascii(c[i]));
	return(0);
}*/
