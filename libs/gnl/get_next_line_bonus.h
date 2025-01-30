/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:16:30 by akitsenk          #+#    #+#             */
/*   Updated: 2024/05/15 11:32:56 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdint.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//# ifndef FD_SIZE
//#  define FD_SIZE 5
//# endif

char	*get_next_line(int fd);
size_t	check_buf_nl(char *buf);
void	move_buf(char *buf);
size_t	cnt_chr(char *next_line, char *buf);
char	*crt_line(char *next_line, char *buf);

#endif
