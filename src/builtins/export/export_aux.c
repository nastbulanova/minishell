/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:56:20 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:56:58 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

void	update_env(t_minishell *data, char *var_name, char *var_value)
{
	t_env	*exist;

	exist = env_retrieve(data->env, var_name);
	if (exist)
		env_update(exist, var_value);
	else
		env_add(&data->env, env_create(var_name, var_value));
	free(var_name);
	var_name = NULL;
	free(var_value);
	var_value = NULL;
}

void	print_error_export(char *arg)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

bool	is_valid_variable_name(const char *name)
{
	int	i;

	if (!name || name[0] == '\0')
		return (false);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = -1;
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
	}
	return (true);
}

void	extract_name_value(char *line, char **name, char **value)
{
	char	*p;

	p = ft_strchr(line, '=');
	*name = ft_substr(line, 0, p - line);
	*value = ft_substr(line, p - line + 1, ft_strlen(p + 1));
}
