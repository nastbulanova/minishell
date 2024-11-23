#include "../inc/builtins.h"


int cmd_pwd(char **str, int fd_out, t_minishell *shell);
{
	char *pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		perror("pwd")
	}

	return (0);
}
