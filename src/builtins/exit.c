#include "../../inc/minishell.h"

static bool arg_numeric(char *arg)
{
	int x;

	x = 0;
	while (arg[x] == '-' || arg[x] == '+')
                x++;
	if (arg[x] == '\0') 
            return (false);
    while (arg[x])
    {
        if (!ft_isdigit(arg[x]))
            return (false);
        x++;
    }
	return (true);
}
bool all_numeric(char **args)
{
    int i;
    int x;

	i = -1;
    while (args[++i])
    {
        x = 0;
        if (i == 0)
        {
            while (args[i][x] == '-' || args[i][x] == '+')
                x++;
        }
        if (args[i][x] == '\0') 
            return (false);
        while (args[i][x])
        {
            if (!ft_isdigit(args[i][x]))
                return (false);
            x++;
        }
    }
    return (true);
}

static int handle_more(char **args)
{
	if (!arg_numeric(args[1]))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		minishell_exit(NULL, 2);
		return (2);
	}
	else
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (2);
	}
}
static void handle_one(char **args)
{
	if (arg_numeric(args[1]))
		minishell_exit("exit\n", ft_atoi(args[1])); // TODO Check max
	else
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		minishell_exit(NULL, 2);
	}
}
int cmd_exit(char **args)
{
	int args_size;

	args_size = array_size(args) - 1;
	if (args_size == 0)
		minishell_exit("exit\n", 0);
	else if (args_size == 1)
		handle_one(args);
	else if (args_size > 1)
		handle_more(args);
	minishell_exit("exit\n", 0);
	return (0);
}
