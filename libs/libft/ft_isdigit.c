/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 13:15:07 by akitsenk          #+#    #+#             */
/*   Updated: 2024/04/25 18:04:30 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
/*int main()
{
	int c[3] = {6, 30, 40};
	int i = -1;

	while (i ++ < 2)
		printf("int %d, result %d\n", c[i], ft_isdigit(c[i]));
	return(0);
}*/
