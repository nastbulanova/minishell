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
void minishell_free(t_minishell *shell);

//builtins/cd
//cd_aux
int array_size(char **split, char **working_arg);
t_env *get_pwd(t_minishell *shell);
//cd_error_handler.c
void cd_error_exit(char *path, int _errno);
//cd_oe_arg
int cd_one_arg(t_minishell *shell, char *working_arg);
//cd.c
int cd_no_args(t_minishell *shell);
int cd_multiple_args(char **str);
int cmd_cd(char **str, int fd_out, t_minishell *data);

//export/exp_init.c
void exp_init(t_minishell *data);
//export/exp_aux.c
void exp_print(t_minishell *data);

t_minishell *get_shell(t_env *env);
void display_splash_screen(void);

#endif
