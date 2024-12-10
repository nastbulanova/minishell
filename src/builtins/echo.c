#include "../../inc/builtins.h"

int cmd_echo(char **args, t_minishell *data)
{
	bool newline;
	int first_arg;

	newline = has_flag(args, "-n");
	first_arg = index_arg(args, get_cmd_flags(args[0]));
	while (first_arg >= 0 && args[first_arg])
	{
		ft_putstr_fd(args[first_arg], STDOUT_FILENO);
		if (args[first_arg + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		first_arg++;
	}
	if (!newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	data->exit_code = 0;
	return (0);
}
