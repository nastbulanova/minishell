#include "minishell.h"

char	*env_var_replace(t_minishell *data, char *name)
{
	int		i;
	int		len;

char **env_list = data
	i = -1;
	name = ft_strjoin(name, "=");
	len = ft_strlen(name);
	while (data->env[++i])/////////////////////////////////////////////////////change logic, have to be linked list
	{
		if (!ft_strncmp(data->env[i], name, len))
			return(ft_substr(data->env[i], len, INT_MAX));
	}
	return (NULL);
}

void	env_var_exp(t_exp_field **field, char *str)
{
	char    *name;
	char    *var_value;

	(*field)->j = (*field)->i + 1;
	while (ft_isalpha(str[(*field)->j]) || str[(*field)->j] == '_')
		(*field)->j++;
	name = ft_substr(str, (*field)->i + 1, (*field)->j - (*field)->i);
	var_value = env_var_replace((*field)->data, name);
	if (var_value)
		(*field)->result = ft_strjoin((*field)->result, ft_strjoin(ft_substr(str, (*field)->start, (*field)->i), var_value));
	else
		(*field)->result = ft_strjoin((*field)->result, ft_substr(str, (*field)->start, (*field)->j));//////////////////////////
	(*field)->i = (*field)->j;
	(*field)->start = (*field)->i;
	free(var_value);
	free(name);
}

void	end_code_exp(t_exp_field **field, char *str)
{
	//////////////////////////////////////////////////////////////////////////////now can't be finished
	(void)str;
	(*field)->i++;
	(*field)->start = (*field)->i;
}

char	*open_field(t_minishell *data, t_token *token)
{
	t_exp_field *field;
	char        *str;

	str = token->start;
	field->i = 0;
	field->j = 0;
	field->result = "";
	field->start = 0;
	field->data = data;
	while (field->i < token->len)
	{
		if (str[field->i] == '$' && str[field->i + 1] == '?')
			end_code_exp(&field, str);
		else if (str[field->i] == '$')
			env_var_exp(&field, str);
		else
			field->i++;
	}
	if (ft_strlen(field->result) == 0)
		return(ft_substr(token->start, 0, token->len));
	else
		return(ft_strjoin(field->result, ft_substr(str, field->j + 1, field->i)));
}
