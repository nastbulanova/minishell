#include "../inc/minishell.h"
void cd_error_exit(char *path, void * _errno) // you have to pass the errno
{
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(strerror(_errno), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
}
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
			error_exit("getcwd error.", "get_pwd @ builtinscd.c");
		result = env_create("PWD", pwd_dup);
		env_add(&shell->env, result);
		free(pwd_dup);
	}
	return (result);
}
int cd_no_args(t_minishell *shell)
{
	t_env *home;
	t_env *oldpwd;
	t_env *pwd;

	home = env_retrieve(shell->env, "HOME");
	oldpwd = env_retrieve(shell->env, "OLDPWD");
	pwd = get_pwd(shell);
	if (home)
	{
		errno = 0;
		chdir(home->value);
		if (!errno)
		{
			cd_error_exit(home->value);
			return (1);
		}
		if (oldpwd)
			env_update(oldpwd, pwd->value);
		else
			env_add(&shell->env, env_create("OLDPWD", pwd->value));
		env_update(pwd, home->value);
	}
	return (0);
}


int cd_one_arg(t_minishell *shell, char *working_arg)
{
	t_env *oldpwd;
	t_env *pwd;
	t_env *home;
	char *swap;

	home = env_retrieve(shell->env, "HOME");
	oldpwd = env_retrieve(shell->env, "OLDPWD");
	pwd = env_retrieve(shell->env, "PWD");
	if (!oldpwd)
		error_exit("OLDPWD not found", "cd_one_arg @ cd.c");
	if (!pwd)
		error_exit("PWD not found", "cd_one_arg @ cd.c");
	if (working_arg[0] == '-')//and it only has a minus
	{
		errno = 0;
		chdir(oldpwd->value);
		if (errno)
			cd_error_exit(working_arg);
		swap = ft_strdup(oldpwd->value);
		env_update(oldpwd, pwd->value);
		env_update(pwd, swap);
		free(swap);
	}
	else if (working_arg[0] == '~' || working_arg[0] == '\0')
	{
		if (!home)
			return (0);
		errno = 0;
		chdir(home->value);
		if (errno)
			cd_error_exit(working_arg);
		env_update(oldpwd, pwd->value);
		env_update(pwd, home->value);
	}
	else if (working_arg[0] == '.')
		env_update(oldpwd, pwd->value);
	return (0);
}
int cmd_cd(char **str, int fd_out, t_minishell *shell)
{
	(void)str;
	(void)fd_out;
	(void)shell;
	char *working_arg = NULL;
	int arg_count = array_size(str, &working_arg) - 1;
	if (arg_count == 0)
		shell->exit_code = cd_no_args(shell);
	else if (arg_count == 1)
		shell->exit_code = cd_one_arg(shell, working_arg);
	else
	{
		
	}
	return (0);
}
