/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:00:38 by akitsenk          #+#    #+#             */
/*   Updated: 2024/05/15 13:20:18 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buf [FOPEN_MAX][BUFFER_SIZE + 1];
	char		*next_line;
	int			flag;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	flag = -1;
	bytes = 1;
	next_line = NULL;
	while (1)
	{
		if (!buf[fd][0])
			bytes = read(fd, buf[fd], BUFFER_SIZE);
		next_line = crt_line(next_line, buf[fd]);
		move_buf(buf[fd]);
		flag = check_buf_nl(next_line);
		if (flag != -1 || bytes <= 0)
			break ;
	}
	if (!next_line[0])
		return (free(next_line), NULL);
	return (next_line);
}
/*int main()
{
    //int		fd0, fd1, fd2;
    char	*line;
	int i = 0;
	int fd;

    fd = open("test.txt", O_RDONLY);
	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	printf("line *%s*", get_next_line(fd0));
	printf("line *%s*", get_next_line(fd1));
	printf("line *%s*", get_next_line(fd2));
	printf("line *%s*", get_next_line(fd0));
	printf("line *%s*", get_next_line(fd1));
	printf("line *%s*", get_next_line(fd2));
	
	// printf("line *%s*", line);
	while(1)
	{
		line = get_next_line(fd);
		printf("line *%s*\n", line);
		free(line);
		
		if (!line)
			break ;
		i ++;
	}
	//free(line);
    close(fd);
	//close(fd1);
	//close(fd2);
    return (0);
}*/
