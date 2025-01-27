#include "../../inc/minishell.h"

int cmd_echo(char **args, int fd)
{
	bool newline;
	int first_arg;

	if (fd < 0)
		fd = STDOUT_FILENO;
	newline = has_flag(args, "-n");
	first_arg = index_arg(args, get_cmd_flags(args[0]));
	while (first_arg >= 0 && args[first_arg])
	{
		ft_putstr_fd(args[first_arg], fd);
		if (args[first_arg + 1])
			ft_putstr_fd(" ", fd);
		first_arg++;
	}
	if (!newline)
		ft_putstr_fd("\n", fd);
	
	if (fd != STDOUT_FILENO)
		close_fd(&fd);
	return (0);
}
