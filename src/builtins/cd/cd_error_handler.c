#include "../../../inc/minishell.h"

void cd_error_exit(char *path, int _errno)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(strerror(_errno), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}

