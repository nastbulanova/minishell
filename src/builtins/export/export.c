#include "../../../inc/minishell.h"

int cmd_export(char** args, t_minishell *data)
{
	int arg_count;
	int first_arg;

	arg_count = array_size(args) - 1;
	if (arg_count == 0)
	{
		exp_print(data);
		data->exit_code = 0;
	}
	else if (arg_count > 0)
	{
		first_arg = index_arg(args, get_cmd_flags(args[0]));
		while (first_arg >= 0 && args[first_arg])
		{
			//check valid
			char *p = ft_strchr(args[first_arg], "=");
			if (p && p != args[first_arg])//exist e e diferente do ponteiro do inicio da string
			{
				//split
				//verificar o nome
				//verificar o valor
			}
			first_arg++;
		}
	}
	
	return (0);
}
