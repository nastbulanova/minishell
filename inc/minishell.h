#ifndef MINISHELL
# define MINISHELL

# include "defines.h"
# include "structs.h"
# include "mini_signals.h"
# include "builtins.h"
# include "executor.h"
# include "executor_tests.h"
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

//common.c
int c_strcmp(char *str_one, char *str_two);
void print_array(char **arr);
void free_array(char **arr, char *temp);
void minishell_exit(char *msg, int exit_code);

//prompt
//prompt_aux.c
char *extract_host(char *session_manager);
void built_left_prompt(char *prompt, char *user, char *local);
//prompt.c
void update_prompt(t_minishell *data);




t_minishell *get_shell(bool init);
void display_splash_screen(void);

#endif
