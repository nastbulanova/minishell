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

SRCS = ${SRC_DIR}/main.c

OBJS = ${patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRCS}}


${NAME} : ${OBJS} | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LINKS)


$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				make libs
				printf "Compiling $(NAME) objects... %-33.33s\r" $(notdir $@)
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


.PHONY: all clean fclean re