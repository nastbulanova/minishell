#ifndef BUILTINS_H
#define BUILTINS_H

# include "minishell.h"

int cmd_echo(char **str, int fd_out, t_minishell *shell);
int cmd_pwd(char **str, int fd_out, t_minishell *shell);


#endif