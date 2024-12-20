#include "../../inc/minishell.h"

int cmd_unset(char **args, t_minishell *data)
{
	int first_arg;
	t_env *to_delete;
	t_env *head;

	head = data->env;
	first_arg = index_arg(args, get_cmd_flags(args[0]));
	while (first_arg >= 0 && args[first_arg])
	{
		to_delete = env_retrieve(data->env, args[first_arg]);
		if (to_delete)
		{
			env_delete(&head, to_delete->name);
			to_delete = NULL;
		}
		first_arg++;
	}
	data->exit_code = 0;
	return (0);
}
