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

static void handle_more(char **args, t_minishell *data)
{
	if (!arg_numeric(args[1]))
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		data->exit_code = 2;
		minishell_exit(NULL, data);
	}
	else
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		data->exit_code = 1;
	}
}
static void handle_one(char **args, t_minishell *data)
{
	if (arg_numeric(args[1]))
	{
		data->exit_code = ft_atoi(args[1]);
		minishell_exit("exit\n", data);
	}
	else
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		data->exit_code = 2;
		minishell_exit(NULL, data);
	}
}
int cmd_exit(char **args, t_minishell *data)
{
	int args_size;

	args_size = array_size(args) - 1;
	if (args_size == 0)
		minishell_exit("exit\n", data);
	else if (args_size == 1)
		handle_one(args, data);
	else if (args_size > 1)
		handle_more(args, data);
	data->exit_code = 0;
	return (0);
}
