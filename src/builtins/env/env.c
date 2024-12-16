#include "../../../inc/minishell.h"

int cmd_env(char** str, t_minishell *data)
{
	(void)str;
	env_print(data->env);
	data->exit_code = 0;
	
	return (0);
}
