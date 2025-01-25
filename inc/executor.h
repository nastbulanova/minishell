#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"
# include "structs.h"


//executor/executor_aux_safe.c
void close_pipe(int pipe_fd[2]);
void safe_pipe(int pipe_fd[2]);
void close_fd(int *fd);
pid_t safe_fork();
void safe_dup_two(int fd, int fd_two);

//executor/executor_aux.c
bool has_output(t_redir *redir);
bool has_input(t_redir *redir);
bool has_heredoc(t_redir *redir);
void init_cmd(t_exec_data *exec_data);

//executor/executor_child_aux
t_pid_list *create_pid_node(pid_t pid);
void add_pid(t_pid_list **head, pid_t pid);
void handle_exit_status(t_pid_list *pid_list);

//executor/executor_child.c
void handle_child(t_exec_data *current, t_exec_data *previous, char **envp);
char *built_error_string(const char* filename);

//executor/executor_free.c
void free_pid_list(t_pid_list **head);
void free_redir(t_redir *redirs);
void free_opt_llist(t_opt_llist *opt_llist);
void free_exec_data_list(t_exec_data *head);

//executor/executor_heredoc.c
void heredoc_loop(t_redir *current, int fd);


//executo/executor_redir.c
void handle_heredoc_redirection(t_exec_data *head);
void handle_other_redirections(t_exec_data *head);

//executor/setup_fd.c

//executor/executor
void execute_command_list(t_exec_data *head, char **envp);



//executor/mock_parser.c
t_redir *create_rdir(t_redir_type type,char *str);
void add_redir_to_list(t_redir **head, t_redir *new_redir);
char **add_string_to_array(char *new_str, char **old_array);
t_exec_data *get_test(int test_number);




#endif