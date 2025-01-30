#include "minishell.h"

char	*env_var_replace(t_minishell *data, char *name)
{
	t_env	*head;
	char    *var_value;

	if (!name)
		return(NULL);
	head = data->env;
	while (head)
	{
		if (!ft_strncmp(head->name, name, ft_strlen(name) + 1))
		{
			if (!head->value)
				var_value = ft_strdup("");
			else
				var_value = ft_strdup(head->value);
			return(var_value);
		}
		head = head->next;
	}
	var_value = ft_strdup("");
	return (var_value);
}

t_parser_error	end_code_exp(t_exp_field **field, char *str)
{
	char	*code;
	char	*temp_result;
	char    *tmp;

	code = ft_itoa((*field)->data->exit_code);
	if (!code)
		return (MALLOC_ERROR);
	tmp = ft_substr(str, (*field)->start, (*field)->i - (*field)->start);
	if (!tmp)
		return(free(code),MALLOC_ERROR);
	temp_result = ft_strjoin((*field)->result, tmp);
	free(tmp);
	free((*field)->result);
	if (!temp_result)
		return(free(code),MALLOC_ERROR);
	(*field)->result = ft_strjoin(temp_result, code);
	free(temp_result);
	free(code);
	if (!(*field)->result)
		return(MALLOC_ERROR);
	(*field)->i += 1;
	(*field)->start = (*field)->i + 1;
	return (OK);
}

char	*get_env_var_value(t_exp_field **field, char *str)
{
	char	*name;
	char	*var_value;

	(*field)->j = (*field)->i + 1;
	while (ft_isalpha(str[(*field)->j]) || str[(*field)->j] == '_' || ft_isalnum(str[(*field)->j]))
		(*field)->j++;
	name = ft_substr(str, (*field)->i + 1, (*field)->j - (*field)->i - 1);
	if (!name)
		return (NULL);
	var_value = env_var_replace((*field)->data, name);
	free(name);
	return (var_value);
}

t_parser_error env_var_exp(t_exp_field **field, char *str)
{
	char	*var_value;
	char	*temp_result;
	char	*substr_result;

	var_value = get_env_var_value(field, str);
	if (!var_value)
		return (MALLOC_ERROR);
	substr_result = ft_substr(str, (*field)->start, (*field)->i - (*field)->start);
	if (!substr_result)
		return (free(var_value), MALLOC_ERROR);
	temp_result = ft_strjoin((*field)->result, substr_result);
	free(substr_result);
	free((*field)->result);
	if (!temp_result)
		return (free(var_value), MALLOC_ERROR);
	(*field)->result = ft_strjoin(temp_result, var_value);
	free(var_value);
	free(temp_result);
	if (!(*field)->result)
		return (MALLOC_ERROR);
	(*field)->i = (*field)->j - 1;
	(*field)->start = (*field)->i + 1;
	return (OK);
}


static t_exp_field *init_field(t_minishell *data)
{
    t_exp_field *field;

    field = malloc(sizeof(t_exp_field));
    if (!field)
        return NULL;
    field->i = 0;
    field->j = 0;
    field->start = 0;
    field->data = data;
    field->result = ft_strdup("");
    if (!field->result)
    {
        free(field);
        return(NULL);
    }
    return field;
}

static t_parser_error fill_field(t_exp_field *field, char *str, int len)
{
    t_parser_error error;

    while (field->i < len)
    {
        if (str[field->i] == '$' && (field->i + 1 < len) && str[field->i + 1] == '?')
        {
            error = end_code_exp(&field, str);
            if (error != OK)
                return (error);
        }
        else if (str[field->i] == '$')
        {
            error = env_var_exp(&field, str);
            if (error != OK)
                return(error);
        }
        else
            field->i++;
    }
    return(OK);
}

static char *finalize_field(t_exp_field *field, char *str)
{
    char *remaining;
    char *temp;
    char *final_result;
    int len_sub;

    len_sub = field->i - field->start;
    remaining = ft_substr(str, field->start, len_sub);
    if (remaining)
    {
        temp = ft_strjoin(field->result, remaining);
        free(remaining);
        if (!temp)
            return NULL;
        free(field->result);
        field->result = temp;
    }
    final_result = field->result;
    return(final_result);
}

char *open_field(t_minishell *data, t_token *token)
{
    t_exp_field *field;
    t_parser_error error;
    char *final_result;

    field = init_field(data);
    if (!field)
        return(NULL);
    error = fill_field(field, token->start, token->len);
    if (error != OK)
    {
        free(field->result);
        free(field);
        return(NULL);
    }
    final_result = finalize_field(field, token->start);
    if (!final_result)
    {
        free(field->result);
        free(field);
        return(NULL);
    }
    free(field);
    return(final_result);
}
