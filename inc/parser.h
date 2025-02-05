#ifndef PARSER
# define PARSER

# include "defines.h"
# include "structs.h"

# define CONST_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"
# define CONST_BUILTIN "echo cd pwd export unset env exit"

t_parser_error	cmd_check(t_minishell **data, char *cmd, int **int_cmd);
t_parser_error	find_path(t_env *env, char *cmd, char **cmd_with_path);

t_opt_llist		*opt_create(char *opt);
char			*opt_check(t_minishell **data, t_token ***token);
t_parser_error	opt_add(t_minishell **data, char *opt);
char			*open_field(t_minishell *data, t_token *token);
char			*env_var_replace(t_minishell *data, char *name);
t_parser_error	redir_check(t_minishell **data, t_token ***token);
t_parser_error	heredoc_check(t_minishell **data, t_token ***token);
t_redir	        *redir_create(char *str, t_token_type type);

//parser_free_utils
void			free_parser_data(t_minishell **data);
void			free_exec_data(t_exec_data *tmp_exec_data);
void			free_opt_llist(t_opt_llist **opt_llist);

//parser_exec_data_utils
t_exec_data		*exec_data_init(void);
t_parser_error	exec_data_append(t_minishell **data, int create);
int				opt_llist_len(t_opt_llist *opt_llist);
char			**opt_llist_to_array(t_opt_llist *opt_llist);

//parser_error_utils
t_parser_error	syntax_error(t_minishell **data, t_token **token);
t_parser_error  memory_error(t_minishell **data);

#endif