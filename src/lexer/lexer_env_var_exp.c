#include "minishell.h"

char	*exp_variable(t_minishell *data, const char *input, int **i)
{
	char	*var_name;
	char	*var_value;
	int		start;
	int		j;

	if (input[**i + 1] == '?')
	{
		**i = **i + 2;
		return (ft_itoa(data->exit_code));
	}
	start = **i + 1;
	j = start;
	while (input[j] != '\0' && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	var_name = ft_substr(input, start, j - start);
	if (var_name == NULL)
		return (NULL);
	if (ft_strlen(var_name) == 0)
		return (**i = j, free(var_name), ft_strdup("$"));
	var_value = env_var_replace(data, var_name);
	free(var_name);
	**i = j;
	return (var_value);
}

char	*exp_loop(t_minishell *data, char *line, int *i, bool *squote)
{
	if (line[*i] == '\'' && *squote == 0)
		return(*squote = 1, (*i)++, ft_strdup("\'"));
	else if (line[*i] == '\'' && *squote == 1)
		return(*squote = 0, (*i)++, ft_strdup("\'"));
	else if (line[*i] == '$' && *squote == 0)
		return(exp_variable(data, line, &i));
	else
		return((*i)++, ft_substr(line, *i - 1, 1));
}

char	*first_line_exp(t_minishell *data, char *line)
{
	bool	squote;
	int		i;
	char	*result;
	char	*tmp;

	result = ft_strdup("");
	if (!result)
		return(NULL);
	squote = 0;
	i = 0;
	while (line[i] != '\0')
	{
		tmp = exp_loop(data, line, &i, &squote);
		result = append_str_to_str(result, tmp);
		free(tmp);
	}

	return(result);
}
