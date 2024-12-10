#include "../../../inc/minishell.h"

int cd_minus(t_env *pwd, t_env *oldpwd, char *working_arg)
{
	char *swap;
	int exit_code;

	exit_code = 0;
	errno = 0;
	chdir(oldpwd->value);
	if (errno)
	{
		cd_error_exit(working_arg, errno);
		exit_code = 1;
	}
	swap = ft_strdup(oldpwd->value);
	env_update(oldpwd, pwd->value);
	env_update(pwd, swap);
	free(swap);
	return (exit_code);
}

int cd_home(t_env **pwd, t_env **oldpwd, t_env **home, char *working_arg)
{
	int exit_code;

	exit_code = 0;
	if (!home)
		return (0);
	errno = 0;
	chdir((*home)->value);
	if (errno)
	{
		cd_error_exit(working_arg, errno);
		exit_code = 1;
	}
	env_update(*oldpwd, (*pwd)->value);
	env_update(*pwd, (*home)->value);
	return (exit_code);
}

int cd_remainder(t_env **oldpwd, t_env **pwd, char *working_arg)
{
	if (working_arg[0] == '.')
		env_update(*oldpwd, (*pwd)->value);
	else
	{
		errno = 0;
		chdir(working_arg);
		if (errno)
		{
			cd_error_exit(working_arg, errno);
			return (1);
		}
		else
		{
			env_update(*oldpwd, (*pwd)->value);
			env_update(*pwd, working_arg);
		}
	}
	return (0);
}

int cd_one_arg(t_minishell *data, char *working_arg)
{
	t_env *oldpwd;
	t_env *pwd;
	t_env *home;
	int len;

	home = env_retrieve(data->env, "HOME");
	oldpwd = env_retrieve(data->env, "OLDPWD");
	pwd = env_retrieve(data->env, "PWD");
	if (!oldpwd)
		error_exit("OLDPWD not found", "cd_one_arg @ cd.c");
	if (!pwd)
		error_exit("PWD not found", "cd_one_arg @ cd.c");
	len = ft_strlen(working_arg);
	
	if (working_arg[0] == '-' && len == 1)
		return(cd_minus(pwd, oldpwd, working_arg));
	else if (working_arg[0] == '~' || working_arg[0] == '\0')
		return(cd_home(&pwd, &oldpwd, &home, working_arg));
	else
		return(cd_remainder(&oldpwd, &pwd, working_arg));
	return (0);
}

