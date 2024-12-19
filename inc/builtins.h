#ifndef BUILTINS_H
# define BUILTINS_H

# include "defines.h"
# include "structs.h"

// builtins/common.c
int		array_size(char **array);
int		index_arg(char **args, char **flags);
char	**get_cmd_flags(char *command);
bool	has_flag(char **args, char *flag);

//echo.c
int		cmd_echo(char **args, t_minishell *data);
//pwd.c
int		cmd_pwd(t_minishell *data);
//unset.c
int     cmd_unset(char **args, t_minishell *data);

//exit.c
bool    all_numeric(char **args);
int		cmd_exit(char **args, t_minishell *data);
// builtins/cd
// cd_one_arg
int		cd_one_arg(t_minishell *shell, char *working_arg);
int		cd_remainder(t_env **oldpwd, t_env **pwd, char *working_arg);
int		cd_home(t_env **pwd, t_env **oldpwd, t_env **home, char *working_arg);
int		cd_minus(t_env *pwd, t_env *oldpwd, char *working_arg);
// cd.c
void	cd_error_exit(char *path, int _errno);
t_env	*get_pwd(t_minishell *shell);
int		cd_no_args(t_minishell *shell);
int		cd_multiple_args(char **str);
int		cmd_cd(char **str, t_minishell *data);

// builtins/export
// export/export_aux.c
void    extract_name_value(char *line, char **name, char **value);
void    update_env(t_minishell *data, char *var_name, char* var_value);
void    print_error_export(char *arg);
//export/export_print.c
void	exp_print(t_minishell *data);
// export/export.c
int		cmd_export(char **str, t_minishell *data);

// builtins/env
// env/env.c
int		cmd_env(char **str, t_minishell *data);
// env/env_init.c
void	env_init(char **argv, char **envp, t_minishell *shell);
void	env_init_default(char **argv, t_minishell *data);
char	*final_path_one(char **sanitized_arg_path, char *pwd);
char	**sanitize_arg_path(char **split_arg_path);
// env/env_path.c
char	*get_path_from_single_array(char **split);
char	*get_path_from_arrays(char **split_pwd, char **split_arg);
// env/env_extract.c
t_env	*env_extract(char *str);
// env/env_aux.c
void	env_add(t_env **head, t_env *new);
void	env_print(t_env *head);
void	env_free(t_env *head);
void shlvl_init(t_env *head);
// envenv_crud
void	env_delete(t_env **head, char *name);
t_env	*env_retrieve(t_env *head, char *name);
t_env	*env_create(char *name, char *value);
void	env_update(t_env *target, const char *new_value);

#endif