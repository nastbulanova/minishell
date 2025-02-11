/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:28:47 by akitsenk          #+#    #+#             */
/*   Updated: 2025/02/11 15:31:21 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "defines.h"
# include "structs.h"

//parser
t_parser_error	parser_loop(t_minishell *data, t_token **token, int *cmd);

//parser_cmd_utils
t_parser_error	cmd_check(t_minishell **data, char *cmd, int **int_cmd);
t_parser_error	loop_path(char **paths, char *cmd, char ***cmd_with_path);
t_parser_error	list_path(t_env *env, char ***paths);
t_parser_error	find_path(t_env *env, char *cmd, char **cmd_with_path);

//parser_opt_utils
t_parser_error	opt_add(t_minishell **data, char *opt);
t_opt_llist		*opt_create(char *opt);

//parser_exp_field_utils_0
char			*open_field(t_minishell *data, t_token *token);

//parser_exp_field_utils_1
char			*env_var_replace(t_minishell *data, char *name);
t_parser_error	end_code_exp(t_exp_field **field, char *str);
char			*get_env_var_value(t_exp_field **field, char *str);
t_parser_error	env_var_exp(t_exp_field **field, char *str);

//parser_exp_field_utils_2
t_parser_error	handle_quotes(t_exp_field *f, char *str, char quote);

//parser_redir_utils
t_redir			*redir_create(char *str, t_token_type type);
t_parser_error	redir_add(t_minishell ***data, char *str, int type);
t_parser_error	redir_check(t_minishell **data, t_token ***token);

//parser_heredoc_utils
int				count_quotes(char *str, int len);
char			*remove_quotes(char *str, int len, t_token_type *type);
t_parser_error	heredoc_check(t_minishell **data, t_token ***token);

//parser_free_utils
void			free_redirs(t_redir **redirs);
void			free_parser_data(t_minishell **data);
void			free_exec_data(t_exec_data *tmp_exec_data);
void			free_opt_llist(t_opt_llist **opt_llist);

//parser_exec_data_utils
t_exec_data		*exec_data_init(void);
t_parser_error	exec_data_append(t_minishell **data, int create);
int				opt_llist_len(t_opt_llist *opt_llist);
char			**opt_llist_to_array(t_opt_llist *opt_llist);
int				opt_llist_len(t_opt_llist *opt_llist);

//parser_error_utils
t_parser_error	syntax_error(t_minishell **data, t_token **token);
t_parser_error	memory_error(t_minishell **data);

#endif