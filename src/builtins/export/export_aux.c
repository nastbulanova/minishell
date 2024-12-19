#include "../../../inc/minishell.h"

void update_env(t_minishell *data, char *var_name, char* var_value)
{
	t_env *exist;

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

void print_error_export(char *arg)
{
	ft_putstr_fd("export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void extract_name_value(char *line, char **name, char **value)
{
	char *p;

	p = ft_strchr(line, '=');
	*name = ft_substr(line, 0, p - line);
	*value = ft_substr(line, p - line + 1, ft_strlen(p + 1));
}