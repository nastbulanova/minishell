/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_one_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:30:24 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/26 15:56:35 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Updates environment variables for PWD and OLDPWD after 
 * a directory change.
 *
 * @param oldpwd Pointer to the OLDPWD environment variable.
 * @param pwd Pointer to the PWD environment variable.
 * @return int Returns 1 on error, 0 on success.
 */
static int	cd_remainder_aux(t_env **oldpwd, t_env **pwd)
{
	char	*pwd_str;

	if (*oldpwd && *pwd)
	{
		pwd_str = NULL;
		pwd_str = getcwd(pwd_str, 0);
		if (!pwd_str)
		{
			ft_putstr_fd("Error: ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			return (1);
		}
		env_update(*oldpwd, (*pwd)->value);
		env_update(*pwd, pwd_str);
		free(pwd_str);
	}
	return (0);
}

/**
 * @brief Handles the 'cd -' command, swapping PWD and OLDPWD.
 *
 * @param pwd Pointer to the PWD environment variable.
 * @param oldpwd Pointer to the OLDPWD environment variable.
 * @param working_arg Unused argument (reserved for future use).
 * @return int Returns 1 on error, 0 on success.
 */
int	cd_minus(t_env *pwd, t_env *oldpwd, char *working_arg)
{
	char	*swap;
	int		exit_code;

	(void)working_arg;
	exit_code = 0;
	errno = 0;
	if (oldpwd && pwd)
	{
		chdir(oldpwd->value);
		if (errno)
		{
			cd_error_exit(oldpwd->value, errno);
			exit_code = 1;
		}
		swap = ft_strdup(oldpwd->value);
		env_update(oldpwd, pwd->value);
		env_update(pwd, swap);
		free(swap);
	}
	return (exit_code);
}

/**
 * @brief Handles the 'cd' command with no arguments or '~', 
 * changing to the home directory.
 *
 * @param pwd Pointer to the PWD environment variable.
 * @param oldpwd Pointer to the OLDPWD environment variable.
 * @param home Pointer to the HOME environment variable.
 * @param working_arg Argument passed to 'cd' (used for error messages).
 * @return int Returns 1 on error, 0 on success.
 */
int	cd_home(t_env **pwd, t_env **oldpwd, t_env **home, char *working_arg)
{
	int	exit_code;

	exit_code = 0;
	if (!*home)
		return (0);
	errno = 0;
	chdir((*home)->value);
	if (errno)
	{
		cd_error_exit(working_arg, errno);
		exit_code = 1;
	}
	if (*oldpwd)
		env_update(*oldpwd, (*pwd)->value);
	if (*pwd)
		env_update(*pwd, (*home)->value);
	return (exit_code);
}

/**
 * @brief Handles 'cd' commands with a specific path.
 *
 * @param oldpwd Pointer to the OLDPWD environment variable.
 * @param pwd Pointer to the PWD environment variable.
 * @param working_arg Directory path provided as an argument.
 * @return int Returns 1 on error, 0 on success.
 */
int	cd_remainder(t_env **oldpwd, t_env **pwd, char *working_arg)
{
	if (working_arg[0] == '.' && working_arg[1] != '.')
		env_update(*oldpwd, (*pwd)->value);
	else
	{
		chdir(working_arg);
		if (errno)
		{
			cd_error_exit(working_arg, errno);
			return (1);
		}
		else
			return (cd_remainder_aux(oldpwd, pwd));
	}
	return (0);
}

/**
 * @brief Determines the appropriate cd behavior based on the argument.
 *
 * @param data Pointer to the shell environment structure.
 * @param working_arg Directory path or special argument for 'cd'.
 * @return int Returns 1 on error, 0 on success.
 */
int	cd_one_arg(t_minishell *data, char *working_arg)
{
	t_env	*oldpwd;
	t_env	*pwd;
	t_env	*home;

	home = env_retrieve(data->env, "HOME");
	oldpwd = env_retrieve(data->env, "OLDPWD");
	pwd = env_retrieve(data->env, "PWD");
	if (working_arg[0] == '-' && ft_strlen(working_arg) == 1)
		return (cd_minus(pwd, oldpwd, working_arg));
	else if (working_arg[0] == '~' || working_arg[0] == '\0')
		return (cd_home(&pwd, &oldpwd, &home, working_arg));
	else
		return (cd_remainder(&oldpwd, &pwd, working_arg));
	return (0);
}
