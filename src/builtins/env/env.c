#include "../../../inc/minishell.h"

int cmd_env()
{
	t_minishell *data;

	data = get_shell(false);
	env_print(data->env);
	return (0);
}
