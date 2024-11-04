NAME = minishell

SRCS = for_test.c lexer.c lexer_utils.c lexer_token_utils.c
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(LIBFT_PATH) -lreadline -fsanitize=address,undefined

LIBFT_PATH = libs/libft/
LIBFT = $(LIBFT_PATH)libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_PATH) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

clean: 
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
