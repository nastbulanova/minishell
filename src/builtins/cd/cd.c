#include "../../../inc/minishell.h"

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
		if (errno)
		{
			cd_error_exit(home->value, errno);
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

int cd_multiple_args(char **str)
{
	ft_putstr_fd("cd: string not in pwd: ", STDERR_FILENO);
	ft_putstr_fd(str[1], STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
	return(1);
}
int cmd_cd(char **str, int fd_out, t_minishell *data)
{
	(void)str;
	(void)fd_out;
	char *working_arg = NULL;
	int arg_count = array_size(str, &working_arg) - 1;
	if (arg_count == 0)
		data->exit_code = cd_no_args(data);
	else if (arg_count == 1)
		data->exit_code = cd_one_arg(data, working_arg);
	else
		data->exit_code = cd_multiple_args(str);
	return (0);
}
