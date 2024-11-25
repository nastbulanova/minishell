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
# include "mini_signals.h"
# include "builtins.h"
# include "../libs/libft/include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

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
	int 		exit_code;

}				t_minishell;



//lexer
t_token	*lexer(char *line);

//lexer_token_utils
t_token	*token_head_init(t_token *token_head);
t_token	*token_create(t_token *head, char *start, int len, int type);

//lexer_utils
int	ft_isspace(int c);
int	ft_iswordchar(int c);
int	ft_isquote(int c);
int	ft_isdblquote(int c);

//parser
int	    parser(t_minishell *data);

//for test
void    print_token(t_token *token);

#endif
