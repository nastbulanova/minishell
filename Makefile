CC = cc

SRC_DIR		= ./src
OBJ_DIR 	= ./obj
INC_DIR		= ./inc
BIN_DIR		= ./bin
LIB_DIR		= ./libs

NAME = ${BIN_DIR}/minishell

LIBFT_PATH = $(LIB_DIR)/libft/

CFLAGS = -Wall -Wextra -Werror -g -Iinc #-fsanitize=address,undefined

LINKS = -lreadline -L$(LIBFT_PATH)lib -lft

SRCS =	${SRC_DIR}/main.c 								${SRC_DIR}/aux.c 								${SRC_DIR}/common.c								\
		${SRC_DIR}/signals/signals.c 					${SRC_DIR}/signals/signals_main.c 				${SRC_DIR}/debug.c								\
		${SRC_DIR}/prompt/prompt.c 						${SRC_DIR}/prompt/prompt_aux.c 																	\
		${SRC_DIR}/builtins/unset.c 					${SRC_DIR}/builtins/exit/exit.c 				${SRC_DIR}/builtins/exit/exit_aux.c				\
		${SRC_DIR}/builtins/echo.c 						${SRC_DIR}/builtins/pwd.c 						${SRC_DIR}/builtins/common.c					\
		${SRC_DIR}/builtins/cd/cd.c 					${SRC_DIR}/builtins/cd/cd_one_arg.c 			${SRC_DIR}/builtins/env/env_init.c 				\
		${SRC_DIR}/builtins/env/env_aux.c 				${SRC_DIR}/builtins/env/env_path.c 				${SRC_DIR}/builtins/env/env_crud.c 				\
		${SRC_DIR}/builtins/env/env_extract.c 			${SRC_DIR}/builtins/env/env.c 					${SRC_DIR}/builtins/export/export_aux.c 		\
		${SRC_DIR}/builtins/export/export_print.c 		${SRC_DIR}/builtins/export/export.c 			${SRC_DIR}/builtins/common_flag.c				\
		${SRC_DIR}/executor/executor_aux_safe.c 		${SRC_DIR}/executor/executor_aux.c 				${SRC_DIR}/executor/executor_child_aux.c 		\
		${SRC_DIR}/executor/executor_child.c 			${SRC_DIR}/executor/executor_common.c 			${SRC_DIR}/executor/executor_command_valid.c	\
		${SRC_DIR}/executor/executor_heredoc.c 			${SRC_DIR}/executor/executor_isolated.c 		${SRC_DIR}/executor/executor_redir.c 			\
		${SRC_DIR}/executor/executor.c 																													\
		${SRC_DIR}/lexer/lexer_char_utils.c 			${SRC_DIR}/lexer/lexer_error_utils.c  			${SRC_DIR}/lexer/lexer_search_utils.c 			\
		${SRC_DIR}/lexer/lexer_token_utils.c 	 		${SRC_DIR}/lexer/lexer.c						${SRC_DIR}/lexer/lexer_env_var_exp.c 			\
		${SRC_DIR}/parser/parser_cmd_utils.c			${SRC_DIR}/parser/parser_cmd_utils2.c			${SRC_DIR}/parser/parser_error_utils.c			\
		${SRC_DIR}/parser/parser_exec_data_utils.c		${SRC_DIR}/parser/parser_exp_field_utils_0.c	${SRC_DIR}/parser/parser_exp_field_utils_1.c	\
		${SRC_DIR}/parser/parser_exp_field_utils_2.c	${SRC_DIR}/parser/parser_free_utils.c			${SRC_DIR}/parser/parser_heredoc_utils.c		\
		${SRC_DIR}/parser/parser_opt_utils.c			${SRC_DIR}/parser/parser_redir_utils.c			${SRC_DIR}/parser/parser.c



#	${SRC_DIR}/executor/mock_parser.c  		${SRC_DIR}/executor/mock_parser_tests.c 								



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

.PHONY: all clean fclean re libs
