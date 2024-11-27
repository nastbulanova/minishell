#ifndef MINISHELL
# define MINISHELL

# include "defines.h"
# include "structs.h"
# include "mini_signals.h"
# include "env.h"
# include "builtins.h"

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

//aux.c
void error_exit(const char *error, const char *function_name);
void *safe_malloc(size_t bytes, const char *function_name);

#endif
