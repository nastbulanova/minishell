/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:05:08 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:06:23 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_final_prompt(char *left, char *right)
{
	char	*final_prompt;
	int		i;
	int		j;

	if (!left)
		return (ft_strdup(right));
	final_prompt = safe_malloc(ft_strlen(left) + ft_strlen(right) + 1);
	i = 0;
	j = 0;
	while (left[i])
	{
		final_prompt[j] = left[i];
		j++;
		i++;
	}
	i = 0;
	while (right[i])
	{
		final_prompt[j] = right[i];
		j++;
		i++;
	}
	return (final_prompt);
}

char	*get_prompt_left(t_minishell *data)
{
	t_env	*user;
	t_env	*session;
	size_t	prompt_len;
	char	*prompt;
	char	*local;

	user = env_retrieve(data->env, "USER");
	session = env_retrieve(data->env, "SESSION_MANAGER");
	local = NULL;
	if (session)
		local = extract_host(session->value);
	if (!user || !user->value || !local || !*local)
	{
		if (local)
			free(local);
		return (NULL);
	}
	prompt_len = ft_strlen(user->value) + ft_strlen(local) + 3;
	prompt = safe_malloc(prompt_len);
	built_left_prompt(prompt, user->value, local);
	free(local);
	return (prompt);
}

char	*get_prompt_right(char *pwd, t_minishell *data)
{
	size_t	home_len;
	size_t	new_pwd_len;
	char	*new_pwd;
	t_env	*home;

	home = env_retrieve(data->env, "HOME");
	if (!pwd || !home || !home->value)
		return (ft_strdup(pwd));
	home_len = strlen(home->value);
	if (ft_strncmp(pwd, home->value, home_len) == 0 && (pwd[home_len] == '/'
			|| pwd[home_len] == '\0'))
	{
		new_pwd_len = strlen(pwd) - home_len + 1;
		new_pwd = safe_malloc(new_pwd_len + 1);
		new_pwd[0] = '~';
		ft_strlcpy(new_pwd + 1, pwd + home_len, new_pwd_len + 1);
		return (new_pwd);
	}
	return (ft_strdup(pwd));
}

char	*get_final_pwd(char *pwd)
{
	char	*final_pwd;
	int		i;

	final_pwd = safe_malloc(ft_strlen(pwd) + 3);
	i = 0;
	while (pwd[i])
	{
		final_pwd[i] = pwd[i];
		i++;
	}
	final_pwd[i] = '$';
	final_pwd[i + 1] = ' ';
	free(pwd);
	return (final_pwd);
}

void	update_prompt(t_minishell *data)
{
	char	*pwd;
	char	*prompt_left;
	char	*prompt_right;

	pwd = NULL;
	if (data->prompt)
		free(data->prompt);
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		data->prompt = ft_strdup("minishell$ ");
		return ;
	}
	pwd = get_final_pwd(pwd);
	prompt_right = get_prompt_right(pwd, data);
	prompt_left = get_prompt_left(data);
	data->prompt = get_final_prompt(prompt_left, prompt_right);
	if (prompt_right)
		free(prompt_right);
	if (prompt_left)
		free(prompt_left);
	free(pwd);
}
