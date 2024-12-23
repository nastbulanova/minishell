#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"
# include "structs.h"

//executor/t_exec_aux.c
void t_extended_exec_data_free(t_extended_exec_data *commands);
void t_extended_exec_data_print(t_extended_exec_data *data, bool no_env, bool no_op);

//executor/mock_parser.c
void execute_commands(t_extended_exec_data *commands, t_minishell *data);
t_extended_exec_data *mock_parser(char *input, t_minishell *data);

#endif