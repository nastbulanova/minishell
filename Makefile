CC = cc

SRC_DIR		= ./src
OBJ_DIR 	= ./obj
INC_DIR		= ./inc
BIN_DIR		= ./bin
LIB_DIR		= ./libs

NAME = ${BIN_DIR}/minishell

LIBFT_PATH = $(LIB_DIR)/libft/

CFLAGS = -Wall -Wextra -Werror -g -Iinc -fsanitize=address,undefined

LINKS = -lreadline -L$(LIBFT_PATH)lib -lft

SRCS =	${SRC_DIR}/main.c ${SRC_DIR}/aux.c\
		${SRC_DIR}/signals/signals.c \
		${SRC_DIR}/builtins/echo.c ${SRC_DIR}/builtins/pwd.c \
		${SRC_DIR}/builtins/cd/cd.c ${SRC_DIR}/builtins/cd/cd_aux.c ${SRC_DIR}/builtins/cd/cd_error_handler.c ${SRC_DIR}/builtins/cd/cd_one_arg.c		\
		${SRC_DIR}/env/env_init.c ${SRC_DIR}/env/env_free.c ${SRC_DIR}/env/env_aux.c ${SRC_DIR}/env/env_crud.c ${SRC_DIR}/env/env_extract.c				\
	#	${SRC_DIR}/lexer/lexer.c ${SRC_DIR}/lexer/lexer_utils.c ${SRC_DIR}/lexer/lexer_token_utils.c \
	#	${SRC_DIR}/parser/parser.c 


OBJS = ${patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRCS}}


${NAME} :	${OBJS} | $(BIN_DIR)
		make libs
		$(CC) $(CFLAGS) $^ -o $@ $(LINKS)


$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)


all: ${NAME}

libs:
	make -C $(LIBFT_PATH)

clean:
	@rm -rf ${OBJ_DIR}
	@echo "Cleaned up object files."

fclean: clean
	@rm -f ${NAME}
	make fclean -C $(LIBFT_PATH)
	@echo "Cleaned up all generated files."

re: fclean all

.PHONY: all clean fclean re