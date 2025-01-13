#include "../../inc/minishell.h"


int cmd_pwd()
{
	char *pwd;
	
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	errno = 0;
	if (!pwd)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
        ft_putstr_fd(strerror(errno), STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        return (1);
	}
	ft_putstr_fd(pwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(pwd);
	return (0);
}
