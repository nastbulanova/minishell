#include "../inc/minishell.h"

int cmd_echo(char** str)
{
	
	int i;
	int non_flag;
	int n_option;

	non_flag = 0;
	n_option = 0;
	if (!str)
	{
		write(1, "\n", 1);
		return (0);
	}

	i = 1;
	while (str[i])
	{
		if (!non_flag && (!ft_strncmp("-n", str[i], 2) || !ft_strncmp("-e", str[i], 2)))
		{
			if (!ft_strncmp("-n", str[i], 2))
				n_option++;
		}
		else
		{
			ft_printf("%s", str[i]);
			non_flag++;
			if (str[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
	if (!n_option)
		write(1, "\n", 1);
	return (0);
}
