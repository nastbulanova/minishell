#ifndef MINISHELL
# define MINISHELL

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <stdbool.h>
# include "libs/libft/libft.h"

# define CONST_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
# define CONST_BUILTIN "echo cd pwd export unset env exit"

typedef enum s_token_type
{
    WORD,
    FIELD,
    EXP_FIELD,
    REDIR_OUT,
	REDIR_IN,
	REDIR_APPEND,
    REDIR_HEREDOC,
	PIPE

}   t_token_type;

typedef struct	s_token
{
	char			*start;
	int				len;
	t_token_type	type;
	int				group;

	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct	s_opt_llist
{
	char				*opt;
	struct	s_opt_llist	*next;
}						t_opt_llist;

typedef enum s_redir_type
{
    OUTPUT,
    OUTPUT_APPEND,
    INPUT,
    HEREDOC,
    HEREDOC_QUOTED

}   t_redir_type;

typedef enum s_parser_error
{
	OK,
    MALLOC_ERROR,
    SYNTAX_ERROR,
	PIPE_ERROR,
	FORK_ERROR

}   t_parser_error;

typedef struct s_redir
{
    t_redir_type    type;
    char            *str; //will be filepath for OUTPUT and INPUT and TERMINATOR for HEREDOC
    struct s_redir  *next;
}   t_redir;

typedef struct  s_exec_data
{
    char                *cmd;
    t_opt_llist         *opt_llist;
    int                 pipe[2];
    char                **opt;
    bool                is_builtin;
    int                 exit_status;
    t_redir             *redirs;
   struct  s_exec_data *next;
}                       t_exec_data;

typedef struct s_env
{
    char 			*name;
    char 			*value;
    struct s_env	*next;
}					t_env;

typedef struct s_minishell
{
	t_token		*token_head;
	t_exec_data	*exec_data;
	t_exec_data	*list_exec_data;
	t_env		*env;
	char		**exec_env;
	int         exit_code;
	char        *prompt;
}				t_minishell;

typedef	struct	s_exp_field
{
	int			i;
	int			j;
	int			start;
	char		*result;
	char		*str;
	t_minishell	*data;
}				t_exp_field;


//lexer
t_parser_error	lexer(t_minishell *data, char *line);

//lexer_char_func
t_parser_error	while_sequence(t_token **token_head, char *line, int (*func)(int), int **i);
t_parser_error	find_field(t_token **token_head, char *line, int (*func)(int), int **i);
t_parser_error	find_redir(t_token **token_head, char *line, char c, int **i);

//lexer_token_utils
t_parser_error token_add(t_token ***token_head, char *start, int len, t_token_type type);
t_token	*token_create(char *start, int len, int type);

//lexer_utils
int		ft_isspace(int c);
int		ft_iswordchar(int c);
int		ft_isquote(int c);
int		ft_isdblquote(int c);
int 	ft_isenvvar(int c);

//lexer_error_utils
t_parser_error   lexer_error(t_token *token_head, t_parser_error error);

//parser
int		parser(t_minishell *data);
t_parser_error	cmd_check(t_minishell **data, char *cmd, int **int_cmd);
t_parser_error	find_path(t_env *env, char *cmd, char **cmd_with_path);
void	free_list(char **list);
t_opt_llist	*opt_create(char *opt);
char	*opt_check(t_minishell **data, t_token ***token);
t_parser_error	opt_add(t_minishell **data, char *opt);
char	*open_field(t_minishell *data, t_token *token);
char	*env_var_replace(t_minishell *data, char *name);
t_parser_error	redir_check(t_minishell **data, t_token ***token);
t_parser_error	heredoc_check(t_minishell **data, t_token ***token);

//parser_free_utils
void    free_parser_data(t_minishell ***data);
void    free_exec_data(t_exec_data *tmp_exec_data);
void    free_opt_llist(t_opt_llist **opt_llist);


//parser_exec_data_utils
t_exec_data	*exec_data_init(void);
t_parser_error	exec_data_append(t_minishell **data, int create);
void	free_array(char **list);
int		opt_llist_len(t_opt_llist *opt_llist);
char	**opt_llist_to_array(t_opt_llist *opt_llist);

//parser_error_utils
int		syntax_error(t_minishell **data, t_token **token);

//exec_utils
int		env_len(t_env *env);
char	**env_list_to_array(t_env *env);

//for test
void    print_token(t_token *token);
t_env	*env_to_linked_list(char **env);
void	print_exec_data(t_minishell *data);


#endif
