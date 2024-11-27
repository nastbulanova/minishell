#include "../inc/builtins.h"


int cmd_pwd(int fd_out, t_minishell *shell)
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
        shell->exit_code = 1; 
        return (1);
	}
	ft_putstr_fd(pwd, fd_out);
	ft_putstr_fd("\n", fd_out);
	free(pwd);
	shell->exit_code = 0;
	return (0);
}
