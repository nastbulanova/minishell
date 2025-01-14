#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"
# include "structs.h"

//executor/executor_aux.c
bool has_output(t_redir *redir);
bool is_last_output(t_redir *redir);
bool is_last_input(t_redir *redir);
bool safe_fd_error(t_redir *temp, char* redir_error, int err_number);
bool safe_fd_error_aux(t_redir *temp, char* redir_error, int err_number);
int call_builtin(t_exec_data *current);

//executor/executor_free.c
void free_redir(t_redir *redirs);
void free_opt_llist(t_opt_llist *opt_llist);
void free_exec_data_list(t_exec_data *head);

//executor/executor_heredoc.c
void heredoc_loop(t_redir *current, int fd);

//executor/executor_pipes.c
void close_pipe(int *pipe_fd);
bool init_pipe(int *pipe_fd);
bool restore_single_pipe(int *previous_pipe);
bool setup_single_pipe(t_exec_data *current, int *previous_pipe);
void manage_pipes(t_exec_data *current, int *previous_pipe);


//executor/setup_fd.c
bool setup_stdin(t_exec_data *current, int* previous_pipe, char* redir_error);
bool setup_stdout(t_exec_data *current, char* redir_error);

//executor/executor
void execute_command(t_exec_data *list_exec_data, char **envp);
void execute_command_chain(t_exec_data *current, int* previous_pipe, char* redir_error, char **envp);
void execute_child(t_exec_data *current, int* previous_pipe, char* redir_error, char **envp);
void execute_command_single(t_exec_data *current, char **envp, bool is_parent);
void process_rdirs(t_exec_data *current, char **redir_error);
void process_rdirs_aux(t_redir *redirs, int *safe_fd, char **redir_error);
void init_cmd(t_exec_data *exec_data);

//executor/mock_parser.c
t_redir *create_rdir(t_redir_type type,char *str);
void add_redir_to_list(t_redir **head, t_redir *new_redir);
char **add_string_to_array(char *new_str, char **old_array);
t_exec_data *get_test(int test_number);




#endif