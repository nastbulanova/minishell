#include "../../inc/minishell.h"

int cmd_unset(char **args)
{
	int first_arg;
	t_env *to_delete;
	t_minishell *data;

	data = get_shell(false);
	first_arg = index_arg(args, get_cmd_flags(args[0]));
	while (first_arg >= 0 && args[first_arg])
	{
		to_delete = env_retrieve(data->env, args[first_arg]);
		if (to_delete)
		{
			env_delete(&data->env, to_delete->name);
			to_delete = NULL;
		}
		first_arg++;
	}
	return (0);
}
