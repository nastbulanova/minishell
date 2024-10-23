CC = cc
CFLAGS = -Wall -Werror -Wextra -Iinc

SRC_DIR		= ./src
OBJ_DIR 	= ./obj
INC_DIR		= ./inc
BIN_DIR		= ./bin
LIB_DIR		= ./lib

NAME = ${BIN_DIR}/minishell

SRCS = ${SRC_DIR}/process/process_aux.c ${SRC_DIR}/signals/signals.c  ${SRC_DIR}/main.c \

OBJS = ${patsubst ${SRC_DIR}/%.c, ${OBJ_DIR}/%.o, ${SRCS}}

all: ${NAME}

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c 
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -c $< -o $@


${NAME} : ${OBJS} 
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	@rm -rf ${OBJ_DIR}
	@echo "Cleaned up object files."

fclean: clean
	@rm -f ${NAME}
	@echo "Cleaned up all generated files."


.PHONY: all clean fclean re