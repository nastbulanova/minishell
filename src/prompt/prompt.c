/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:05:08 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/02 15:58:40 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * @brief Concatenates two strings to form the final prompt.
 *
 * @param left The left part of the prompt (e.g., user info).
 * @param right The right part of the prompt (e.g., directory info).
 * @return A newly allocated string containing the full prompt.
 */
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

/**
 * @brief Constructs the left part of the shell prompt based on user
 * and session info.
 *
 * @param data Pointer to the Minishell data structure.
 * @return A newly allocated string containing the left prompt, or 
 * NULL if unavailable.
 */
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

/**
 * @brief Constructs the right part of the shell prompt, handling home 
 * directory abbreviation.
 *
 * @param pwd The current working directory.
 * @param data Pointer to the Minishell data structure.
 * @return A newly allocated string containing the formatted directory 
 * path.
 */
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
			|| pwd[home_len] == '\0' || pwd[home_len] == '$'))
	{
		new_pwd_len = strlen(pwd) - home_len + 1;
		new_pwd = safe_malloc(new_pwd_len + 1);
		new_pwd[0] = '~';
		ft_strlcpy(new_pwd + 1, pwd + home_len, new_pwd_len + 1);
		return (new_pwd);
	}
	return (ft_strdup(pwd));
}

/**
 * @brief Formats the working directory string by appending "$ " at the end.
 *
 * @param pwd The current working directory.
 * @return A newly allocated string containing the formatted directory path.
 */
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

/**
 * @brief Updates the shell prompt by retrieving user, session, and 
 * working directory info.
 *
 * @param data Pointer to the Minishell data structure.
 */
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
