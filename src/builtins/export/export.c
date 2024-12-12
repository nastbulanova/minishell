#include "../../../inc/minishell.h"

int cmd_export(char** str, t_minishell *data)
{
	int arg_count;

	arg_count = array_size(str) - 1;
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
