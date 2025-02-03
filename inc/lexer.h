#ifndef LEXER
# define LEXER

# include "defines.h"
# include "structs.h"

//lexer_char_utils
t_parser_error	while_sequence(t_token **token_head, char *line, int (*func)(int), int **i);
t_parser_error	find_field(t_token **token_head, char *line, int (*func)(int), int **i);
t_parser_error	find_redir(t_token **token_head, char *line, char c, int **i);

//lexer_token_utils
t_parser_error 	token_add(t_token ***token_head, char *start, int len, t_token_type type);
t_token			*token_create(char *start, int len, int type);

//lexer_utils
int				ft_isspace(int c);
int				ft_iswordchar(int c);
int				ft_isquote(int c);
int				ft_isdblquote(int c);
int 			ft_isenvvar(int c);

//lexer_error_utils
t_parser_error	lexer_error(t_token *token_head, t_parser_error error);

#endif