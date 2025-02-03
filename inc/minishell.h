#ifndef MINISHELL
# define MINISHELL

# include "defines.h"
# include "structs.h"
# include "mini_signals.h"
# include "builtins.h"
# include "executor.h"
# include "executor_tests.h"
# include "parser.h"
# include "lexer.h"

//lexer

t_parser_error  lexer(t_minishell *data, char *line);


//parser
t_parser_error parser(t_minishell *data);


//aux.c
void error_exit(const char *error, const char *function_name);
void *safe_malloc(size_t bytes);
void minishell_free(t_minishell *shell);

//common.c
int c_strcmp(char *str_one, char *str_two);
void print_array(char **arr);
void free_array(char **arr, char *temp);
void minishell_exit(char *msg, int exit_code, int exit_fd, bool dispose_msg);

//prompt
//prompt_aux.c
char *extract_host(char *session_manager);
void built_left_prompt(char *prompt, char *user, char *local);
//prompt.c
void update_prompt(t_minishell *data);


t_minishell *get_shell(bool init);
void display_splash_screen(void);

#endif
