#ifndef BUILTINS_H
#define BUILTINS_H

# include "defines.h"
# include "structs.h"

int cmd_echo(char **str, int fd_out, t_minishell *shell);
int cmd_pwd(int fd_out, t_minishell *shell);


#endif