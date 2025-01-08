#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"
# include "structs.h"

//executor/t_exec_aux.c
void t_extended_exec_data_free(t_extended_exec_data *commands);
void t_extended_exec_data_init(t_extended_exec_data *exec_data);
void close_pipe(int *pipe_fd);

//executor/mock_parser.c
t_extended_exec_data *mock_parser(t_minishell *data);

//executor/t_exec_errors.c
bool fd_open_failure(char *file, char *err_str);
bool pipe_open_failure(char *msg);
bool pipe_init(int *pipe_fd);

//executor/t_exec.c
void execute_command(t_extended_exec_data *exec_data, t_minishell *data);
#endif