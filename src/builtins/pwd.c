#include "../inc/builtins.h"


int cmd_pwd(char **str, int fd_out, t_minishell *shell)
{
	char *pwd;
	
	(void)str;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	ft_putstr_fd(pwd, fd_out);
	ft_putstr_fd("\n", fd_out);
	shell->exit_code = 0;
	return (0);
}
