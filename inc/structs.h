/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:37:22 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/20 15:02:07 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "defines.h"

typedef struct s_pid_list
{
	pid_t				pid;
	struct s_pid_list	*next;
}						t_pid_list;

typedef struct s_redir
{
	t_redir_type		type;
	char				*str;
	char				*error;
	struct s_redir		*next;
}						t_redir;

typedef struct s_opt_llist
{
	char				*opt;
	struct s_opt_llist	*next;
}						t_opt_llist;

typedef struct s_exec_data
{
	char				*cmd;
	t_opt_llist			*opt_llist;
	int					outpipe[2];
	int					input_fd;
	int					output_fd;
	char				**opt;
	bool				is_builtin;
	int					exit_status;
	t_redir				*redirs;
	struct s_exec_data	*next;
}						t_exec_data;

typedef struct s_token
{
	char				*start;
	int					len;
	t_token_type		type;
	int					group;

	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_minishell
{
	int					heredoc_pipe[2];
	t_token				*token_head;
	t_exec_data			*exec_data;
	t_exec_data			*list_exec_data;
	t_env				*env;
	char				**exec_env;
	int					exit_code;
	char				*prompt;
}						t_minishell;

typedef struct s_exp_field
{
	int					i;
	int					j;
	int					start;
	char				*result;
	char				*str;
	t_minishell			*data;
}						t_exp_field;

#endif