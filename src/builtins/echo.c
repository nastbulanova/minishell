#include "../inc/builtins.h"

static void print_string(char **str, int i, int *non_flag_args, int fd_out)
{
	ft_putstr_fd(str[i], fd_out);
	(*non_flag_args)++;
	if (str[i + 1])
		write(fd_out, " ", 1);
}
static int is_flag_lower_n(char *str)
{
	return (ft_strncmp("-n", str, 3) == 0);
}
static int is_flag(char *str)
{
	return (!ft_strncmp("-E", str, 3)
		|| !ft_strncmp("-e", str, 3)
		|| !ft_strncmp("-n", str, 3));
}
int cmd_echo(char** str, int fd_out, t_minishell *shell)
{
	int i;
	int non_flag_args;
	int newline = TRUE;

	non_flag_args = 0;
	i = 1;
	while (str[i])
	{
		if (!non_flag_args && is_flag(str[i]))
		{
			if (is_flag_lower_n(str[i]))
				newline = FALSE;
		}
		else
			print_string(str, i, &non_flag_args, fd_out);
		i++;
	}
	if (newline)
		write(fd_out, "\n", 1);
	shell->exit_code = 0;
	return (0);
}
