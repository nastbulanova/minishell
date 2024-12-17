#include "../../../inc/minishell.h"

void print_error_export(char *arg)
{
	//export: `1VAR': not a valid identifier
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

bool is_valid_variable_name(const char *name) 
{
	int i;

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
void free_name_value(char *name, char* value)
{
	if (name)
		free(name);
	if(value)
		free(value);
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
			var_value = NULL;
		}
		result = is_valid_variable_name(var_name);
		if (result)
			update_env(data, var_name, var_value);
		else
			free_name_value(var_name, var_value);
	}
	return (result);
}
int cmd_export(char** args, t_minishell *data)
{
	int arg_count;
	int first_arg;
	int count_error;

	count_error = 0;
	arg_count = array_size(args) - 1;
	if (arg_count == 0)
		exp_print(data);
	else if (arg_count > 0)
	{
		first_arg = index_arg(args, get_cmd_flags(args[0]));
		while (first_arg >= 0 && args[first_arg])
		{			
			if (!process_arg(args[first_arg], data) && !count_error)
			{
				count_error++;
				print_error_export(args[first_arg]);
			}	
		first_arg++;
		}
	}
	if (count_error == 0)
		data->exit_code = 0;
	else
		data->exit_code = 1;
	return (0);
}
