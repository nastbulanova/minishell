#include "../../../inc/minishell.h"

bool arg_numeric(char *arg)
{
	int x;

	x = 0;
	while (arg[x] == '-' || arg[x] == '+')
                x++;
	if (x > 1 || arg[x] == '\0')
            return (false);
    while (arg[x])
    {
        if (!ft_isdigit(arg[x]))
            return (false);
        x++;
    }
	return (true);
}

static int handle_more(char **args)
{
	if (!arg_numeric(args[1]))
	{
		minishell_exit(built_exit_string(args[1]), 2, STDERR_FILENO, false);
		return (2);
	}
	else
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (2);
	}
}
static void handle_one(char **args)
{
	char exit_code;

	if (arg_numeric(args[1]))
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit_code = ft_exit_atoi(args[1]);
		minishell_exit(NULL, exit_code, STDOUT_FILENO, false);
	}
	else
		minishell_exit(built_exit_string(args[1]), 2, STDERR_FILENO, false);
}
int cmd_exit(char **args)
{
	int args_size;

	args_size = array_size(args) - 1;
	if (args_size == 0)
		minishell_exit("exit\n", 0, STDOUT_FILENO,false);
	else if (args_size == 1)
		handle_one(args);
	else if (args_size > 1)
		handle_more(args);
	minishell_exit("exit\n", 0, STDOUT_FILENO, false);
	return (0);
}
