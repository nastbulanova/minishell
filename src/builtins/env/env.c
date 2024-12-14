#include "../../../inc/minishell.h"

int cmd_env(char** str, t_minishell *data)
{
	
	env_print(data);
	data->exit_code = 0;
	
	return (0);
}
