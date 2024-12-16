#include "../../../inc/minishell.h"
void extract_name_value(char *line, char **name, char **value)
{
	char *p;

	p = ft_strchr(line, '=');
	*name = ft_substr(line, 0, p - line);
	*value = ft_substr(line, p - line + 1, ft_strlen(p + 1));
}

bool is_valid_variable_name(const char *name) 
{
	int i;

    if (!name || name[0] == '\0') 
        return false;
    if (!ft_isalpha(name[0]) && name[0] != '_')
		return false;
	i = -1;
    while (name[++i])
	{
        if (!ft_isalnum(name[i]) && name[i] != '_') 
            return false;
	}
    return true;
}
void update_env(t_minishell *data, char *var_name, char* var_value)
{
	t_env *exist;

	exist = env_retrieve(data->env, var_name);
	if (exist)
		env_update(exist, var_value);
	else
		env_add(&data->env, env_create(var_name, var_value));
	free(var_name);
	free(var_value);
}
bool process_arg(char *arg, t_minishell *data)
{
	char *var_name;
	char *var_value;
	char *p;
	bool result;

	result = false;
	p = ft_strchr(arg, '=');
	if ((p && p != arg) || (!p && is_valid_variable_name(arg)))
	{
		result = true;
		if (p)
			extract_name_value(arg, &var_name, &var_value);
		else
		{
			var_name = ft_strdup(arg);
			var_value = ft_strdup("");
		}
		result = is_valid_variable_name(var_name);
		if (result)
			update_env(data, var_name, var_value);
	}
	return (result);
}
int cmd_export(char** args, t_minishell *data)
{
	int arg_count;
	int first_arg;
	bool allvalid;

	arg_count = array_size(args) - 1;
	if (arg_count == 0)
	{
		exp_print(data);
		data->exit_code = 0;
	}
	else if (arg_count > 0)
	{
		first_arg = index_arg(args, get_cmd_flags(args[0]));
		allvalid = true;
		while (first_arg >= 0 && args[first_arg])
		{
			if (allvalid)
				allvalid = process_arg(args[first_arg], data);
			first_arg++;
		}
		if (allvalid)
			data->exit_code = 0;
		else
			data->exit_code = 1;
	}

	return (0);
}
