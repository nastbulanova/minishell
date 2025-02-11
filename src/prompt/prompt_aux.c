/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:06:36 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/11 18:10:05 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/**
 * @brief Constructs the left part of the shell prompt.
 *
 * This function builds the left part of the prompt using the given 
 * user and local host.
 * The format will be "user@local:".
 *
 * @param prompt The destination buffer where the prompt will be built.
 * @param user The username to include in the prompt.
 * @param local The hostname to include in the prompt.
 */
void	built_left_prompt(char *prompt, char *user, char *local)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (user)
	{
		while (user[j])
		{
			prompt[i] = user[j];
			j++;
			i++;
		}
	}
	prompt[i] = '@';
	i++;
	j = 0;
	while (local[j])
	{
		prompt[i] = local[j];
		j++;
		i++;
	}
	prompt[i] = ':';
}

/**
 * @brief Resolves the session manager host prefix.
 *
 * This function identifies whether the session manager contains a 
 "local/" or "unix/" prefix.
 * It sets the start pointer to the appropriate location and updates
 *  the start length accordingly.
 *
 * @param session_manager The session manager string to be analyzed.
 * @param start_len Pointer to store the length of the prefix found.
 * @param start Pointer to store the start position of the host.
 */
static void	resolve_host(char *session_manager, size_t *start_len, char **start)
{
	*start = NULL;
	*start_len = ft_strlen("local/");
	*start = ft_strnstr(session_manager, "local/", *start_len);
	if (!*start)
	{
		*start_len = ft_strlen("unix/");
		*start = ft_strnstr(session_manager, "unix/", *start_len);
	}
	if (!*start)
		*start_len = 0;
}

/**
 * @brief Extracts the hostname from a session manager string.
 *
 * This function searches for a hostname in the given session manager string by
 * identifying common prefixes ("local/" or "unix/") and extracting the substring
 * up to the first dot ('.').
 *
 * @param session_manager The session manager string to extract the host from.
 * @return A dynamically allocated string containing the extracted hostname,
 *         or NULL if extraction fails.
 */
char	*extract_host(char *session_manager)
{
	char	*start;
	char	*end;
	size_t	start_len;
	size_t	session_len;
	char	*session;

	if (!session_manager)
		return (NULL);
	resolve_host(session_manager, &start_len, &start);
	if (!start)
		return (NULL);
	start += start_len;
	end = ft_strchr(start, '.');
	if (!end)
		return (NULL);
	session_len = (end - start) + 1;
	session = safe_malloc(session_len + 1);
	ft_strlcpy(session, start, session_len);
	return (session);
}
