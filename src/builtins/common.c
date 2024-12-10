#include "../../inc/minishell.h"

int index_arg(char **args, char **flags)
{
    int i; 
    int j;
    int is_flag;

    if (!args || !args[0])
        return (-1);
    i = 1;
    while (args[i]) 
    {
        is_flag = 0;
        j = 0;
        while(flags && flags[j])
        {
            if (!c_strcmp(args[i], flags[j]))
            {
                is_flag = 1;
                break;
            }
            j++;
        }
        if (!is_flag)
            return (i);
        i++;
    }
    return (-1);
}

int array_size(char **array)
{
	int result;

	result = 0;
	if (!array)
		return (result);
	while (array[result])
        result++;
	return (result);
}

bool has_flag(char **args, char *flag)
{
    int first_arg;
    int i;
    char **flags;

    if (!args || !args[0])
        return (false); 
    if (!flag)
        return (false); 
    flags = get_cmd_flags(args[0]);
    if (!flags)
        return (false);
    first_arg = index_arg(args, get_cmd_flags(args[0]));
    if (first_arg < 0)
        first_arg = array_size(args);
    i = -1;
    while (++i < first_arg)
    {
        if (!c_strcmp(flag, args[i]))
            return (true);
    }
    return (false);
}

char	**get_cmd_flags(char *command)
{
	static char	*echo_flags[] = {"-n", "-e", "-E", NULL};
	static char	*cd_flags[] = {"-L", "-P", NULL};
	static char	*pwd_flags[] = {NULL};
	static char	*export_flags[] = {NULL};
    static char	*unset_flags[] = {"-v", "-f", NULL};
	static char	*env_flags[] = {NULL};
    static char	*exit_flags[] = {NULL};

	if (!command)
		return (NULL);
	if (!c_strcmp(command, "echo"))
		return (echo_flags);
	else if (!c_strcmp(command, "cd"))
		return (cd_flags);
	else if (!c_strcmp(command, "pwd"))
		return (pwd_flags);
	else if (!c_strcmp(command, "export"))
		return (export_flags);
	else if (!c_strcmp(command, "unset"))
		return (unset_flags);
	else if (!c_strcmp(command, "env"))
		return (env_flags);
	else if (!c_strcmp(command, "exit"))
		return (exit_flags);
	return (NULL);
}
