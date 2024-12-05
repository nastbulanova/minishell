#ifndef STRUCTS_H
# define STRUCTS_H

#include "defines.h"

typedef struct s_shell_info
{
    int		exit_code;

}t_shell_info;

typedef struct	s_token
{
	char			*start;
	int				len;
	int				type;
	int				group;

	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_exec_data
{
	char	*cmd;
	char	**opt;
	char	**env;
	int		is_pipe;
	int		pipe[2];
	char	*infile;
	char	*new_outfile;
	char	*exist_outfile;

}				t_exec_data;

typedef struct s_minishell
{
	t_token		*token_head;
	t_exec_data	*exec_data;
	t_env 		*env;
	t_env		*exp;
	int 		exit_code;

}				t_minishell;


typedef struct s_env
{
    char	*name;
    char	*value;
	bool	visible;
    struct s_env *next;
} t_env;


#endif
