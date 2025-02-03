#include "../../../inc/minishell.h"

void cd_error_exit(char *path, int _errno)
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(strerror(_errno), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}

t_env *get_pwd(t_minishell *data)
{
	t_env *result;
	char *pwd_dup;

	pwd_dup = NULL;
	result = env_retrieve(data->env, "PWD");
	if (!result)
	{
		pwd_dup = getcwd(NULL, 0);
		if (!pwd_dup)
			error_exit("getcwd error.", "get_pwd @ builtins/cd/cd_aux.c");
		result = env_create("PWD", pwd_dup);
		env_add(&data->env, result);
		free(pwd_dup);
	}

	return (result);
}

int cd_no_args(t_minishell *data)
{
	t_env *home;
	t_env *oldpwd;
	t_env *pwd;

	home = env_retrieve(data->env, "HOME");
	oldpwd = env_retrieve(data->env, "OLDPWD");
	pwd = get_pwd(data);
	if (home)
	{
		errno = 0;
		chdir(home->value);
		if (errno)
		{
			cd_error_exit(home->value, errno);
			return (1);
		}
		if (oldpwd)
			env_update(oldpwd, pwd->value);
		else
			env_add(&data->env, env_create("OLDPWD", pwd->value));
		env_update(pwd, home->value);
	}
	return (0);
}

int cd_multiple_args(char **str)
{
	ft_putstr_fd("cd: string not in pwd: ", STDERR_FILENO);
	ft_putstr_fd(str[1], STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
	return(1);
}

int cmd_cd(char **str)
{
	t_minishell *data;

	data = get_shell(false);
	int arg_count = array_size(str) - 1;
	if (arg_count == 0)
		return (cd_no_args(data));
	else if (arg_count == 1)
		return(cd_one_arg(data, str[1]));
	else
		return(cd_multiple_args(str));
}
