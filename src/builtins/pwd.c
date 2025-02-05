#include "../../inc/minishell.h"


int cmd_pwd(int fd)
{
	char *pwd;
	
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	errno = 0;
	if (fd < 0)
		fd = STDOUT_FILENO;
	if (!pwd)
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
        ft_putstr_fd(strerror(errno), STDERR_FILENO);
        ft_putstr_fd("\n", STDERR_FILENO);
        return (1);
	}
	ft_putstr_fd(pwd, fd);
	ft_putstr_fd("\n", fd);
	free(pwd);
	return (0);
}
