#include "../inc/minishell.h"

int cmd_export(char** str, int fd_out, t_minishell *data)
{
	(void)fd_out;
	int arg_count;

	arg_count = array_len(str) - 1;
	if (arg_count == 0)
	{
		exp_print(data);
		data->exit_code = 0;
	}
	else if (arg_count == 1)
	{

	}
	else
	{

	}
	return (0);
}
