/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:36:04 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/02 15:39:04 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "defines.h"
# include "structs.h"

void		execute_execve(t_exec_data *cmd, t_minishell *data,
				t_exec_data *head);
void		execute_non_pipe(t_minishell *data, t_exec_data *cmd);
void		clear_fds(t_exec_data *temp);
bool		command_is_valid(t_exec_data *cmd, t_minishell *data);

// executor/executor_aux_safe.c
bool		close_fd(int *fd);
bool		close_pipe(int pipe_fd[2]);
bool		safe_pipe(int pipe_fd[2]);
bool		safe_dup_two(int fd, int fd_two);

// executor/executor_aux.c
int			execute_builtin(t_exec_data *cmd, int stdin_backup,
				int stdout_backup);
void		close_command_fds(t_exec_data *cmd);
char		*get_err_str(char *filename, char *error_str, bool newline);

// executor/executor_common.c
bool		has_heredoc(t_redir *redir);
bool		has_input(t_redir *redir);
bool		has_output(t_redir *redir);
char		*get_rdir_error(t_redir *redir);
void		init_cmd(t_exec_data *exec_data);

// executor/executor_child_aux
t_pid_list	*create_pid_node(pid_t pid);
void		add_pid(t_pid_list **head, pid_t pid);
void		handle_exit_status(t_minishell *data, t_pid_list *pid_list);

// executor/executor_child.c
void		handle_child(t_exec_data *cmd, t_exec_data *previous,
				t_exec_data *head);
void		handle_parent(t_exec_data *cmd, t_exec_data *previous,
				t_pid_list **pid_list, pid_t pid);

// executor/executor_free.c
void		free_pid_list(t_pid_list **head);

// executor/executor_heredoc.c
void		heredoc_loop(t_redir *current, int fd);

// executo/executor_redir.c
void		handle_heredoc_redirection(t_minishell *data, t_exec_data *head);
void		handle_io_redirections(t_exec_data *cmd);

// executor/setup_fd.c

// executor/executor
void		execute_command_list(t_minishell *data, t_exec_data *head);
bool		command_is_valid(t_exec_data *cmd, t_minishell *data);

// executor/mock_parser.c
// this function will have to be deleted on the final version
// t_redir *create_rdir(t_redir_type type,char *str);

// void add_redir_to_list(t_redir **head, t_redir *new_redir);
// char **add_string_to_array(char *new_str, char **old_array);
// t_exec_data *get_test(int test_number);

#endif