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
# include "libs/libft/libft.h"

# define START 0
# define AFTERCMD 1
# define AFTEROPT 2


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
	char		**env;

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
t_token	*lexer(char *line);

//lexer_token_utils
t_token	*token_head_init(t_token *token_head);
t_token	*token_create(t_token *head, char *start, int len, int type);

//lexer_utils
int		ft_isspace(int c);
int		ft_iswordchar(int c);
int		ft_isquote(int c);
int		ft_isdblquote(int c);
int 	ft_isenvvar(int c);

//parser
int		parser(t_minishell *data);
char	*cmd_check(t_token *token, char **env);
void	opt_check(t_minishell **data, t_token **token);
char	*open_field(t_minishell *data, t_token *token);
char	*env_var_replace(t_minishell *data, char *name);
void	redir_check(t_minishell **data, t_token **token);


//for test
void    print_token(t_token *token);

#endif