NAME = minishell
SRCS = for_test.c env_to_ll.c \
		lexer.c lexer_char_utils.c lexer_token_utils.c lexer_error_utils.c lexer_search_utils.c\
		parser.c parser_cmd_utils.c parser_cmd_utils2.c parser_exp_field_utils_test.c parser_opt_utils.c \
		parser_redir_utils.c parser_exec_data_utils.c parser_free_utils.c parser_error_utils.c\
		libs/gnl/get_next_line_bonus.c libs/gnl/get_next_line_utils_bonus.c
OBJ_DIR = objects
OBJS = $(addprefix $(OBJ_DIR)/,$(SRCS:.c=.o))
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I libs/gnl/
LIBFT_PATH = libs/libft/
LIBFT = $(LIBFT_PATH)libft.a
LDFLAGS = -L$(LIBFT_PATH)
LDLIBS = -lft -lreadline -lhistory -lncurses

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
