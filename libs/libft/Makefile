# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akitsenk <akitsenk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 10:32:48 by akitsenk          #+#    #+#              #
#    Updated: 2024/05/03 10:47:43 by akitsenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	= ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isalnum.c ft_isprint.c ft_memcpy.c\
		ft_strlen.c ft_bzero.c ft_memset.c ft_memcmp.c ft_memchr.c ft_memmove.c\
		ft_strlcat.c ft_strlcpy.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c\
		ft_atoi.c ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c ft_strtrim.c\
		ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_strjoin.c\
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\

BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c\
		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c\
		ft_lstmap.c\

OBJS	= $(SRCS:.c=.o)

BONUS_OBJS	= $(BONUS:.c=.o)

AR		= ar r
RM		= rm -f
GCC		= cc
CFLAGS 	= -Wall -Wextra -Werror

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: bonus_target

bonus_target: $(BONUS_OBJS) $(OBJS)
	$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)
	touch bonus_target

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUS_OBJS) bonus_target

fclean: clean
	$(RM) $(NAME)

re: fclean all
