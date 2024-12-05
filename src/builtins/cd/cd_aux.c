#include "../../../inc/minishell.h"

int array_size(char **split, char **working_arg)
{
	int result;
	int i;

	result = 0;
	i = 0;
	if (!split)
		return (result);
	while (split[i])
	{
		if (ft_strncmp(split[i], "-P", 3) && ft_strncmp(split[i], "-L", 3))
		{
			result++;
			*working_arg = split[i];
		}
		i++;
	}
	return (result);
}

t_env *get_pwd(t_minishell *shell)
{
	t_env *result;
	char *pwd_dup;

	pwd_dup = NULL;
	result = env_retrieve(shell->env, "PWD");
	if (!result)
	{
		pwd_dup = getcwd(NULL, 0);
		if (!pwd_dup)
			error_exit("getcwd error.", "get_pwd @ builtins/cd/cd_aux.c");
		result = env_create("PWD", pwd_dup);
		env_add(&shell->env, result);
		free(pwd_dup);
	}
	return (result);
}

