/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:00:44 by akitsenk          #+#    #+#             */
/*   Updated: 2025/03/01 21:50:14 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "defines.h"
# include "structs.h"

//lexer_search_utils
t_parser_error	while_sequence(t_token **token_head, char *line, int **i);
t_parser_error	find_field(t_token **token_head, char *line,
					int (*func)(int), int **i);
t_parser_error	find_redir(t_token **token_head, char *line, char c, int **i);
t_parser_error	check_char(t_token **token_head, char *line, int *i);

//lexer_token_utils
t_parser_error	token_add(t_token **token_head, char *start, int len,
					t_token_type type);
t_token			*token_create(char *start, int len, int type);
void			token_append(t_token **token_head, t_token *token);
int				is_last_token_pipe(t_token *head);
t_parser_error	tokenize_str(t_token **token_head, char *line);

//lexer_char_utils
int				ft_isspace(int c);
int				ft_iswordchar(int c);
int				ft_isquote(int c);
int				ft_isdblquote(int c);

//lexer_error_utils
void			token_clean(t_token *token_head);
t_parser_error	lexer_error(t_token *token_head, t_parser_error error);

//lexer_env_var_exp
char			*exp_loop(t_minishell *data, char *line, int *i, bool *squote);
char			*first_line_exp(t_minishell *data, char *line);

//lexer
t_parser_error	get_line(t_minishell *data, int *pipe_fd, char **line);
t_parser_error	process_line(t_minishell *data, int *pipe_fd);
t_parser_error	finish_line(t_minishell *data, char **new_line);

#endif