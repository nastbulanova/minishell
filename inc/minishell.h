/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:36:56 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/26 13:56:40 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include "defines.h"
# include "executor.h"
# include "lexer.h"
# include "mini_signals.h"
# include "parser.h"
# include "structs.h"

// lexer

t_parser_error	lexer(t_minishell *data, char *line);

// parser
t_parser_error	parser(t_minishell *data);
bool			dirty_check(t_token *input);

// aux.c
bool			is_string_empty(char *input);
void			error_exit(const char *error, const char *function_name);
void			*safe_malloc(size_t bytes);
void			minishell_free(t_minishell *shell);

// common.c
int				c_strcmp(char *str_one, char *str_two);
void			print_array(char **arr);
void			free_array(char **arr, char *temp);
void			minishell_exit(char *msg, int exit_code, int exit_fd,
					bool dispose_msg);

// prompt
// prompt_aux.c
char			*extract_host(char *session_manager);
void			built_left_prompt(char *prompt, char *user, char *local);
// prompt.c
void			update_prompt(t_minishell *data);

t_minishell		*get_shell(bool init);

#endif
