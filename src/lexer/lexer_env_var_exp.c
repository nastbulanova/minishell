/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_env_var_exp.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:16:46 by akitsenk          #+#    #+#             */
/*   Updated: 2025/03/01 21:55:53 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	**i = j;
	return (free(var_name), var_value);
}

char	*exp_loop(t_minishell *data, char *line, int *i, bool *squote)
{
	if (line[*i] == '\'' && *squote == 0)
		return (*squote = 1, (*i)++, ft_strdup("\'"));
	else if (line[*i] == '\'' && *squote == 1)
		return (*squote = 0, (*i)++, ft_strdup("\'"));
	else if (line[*i] == '$' && *squote == 0)
		return (exp_variable(data, line, &i));
	else
		return ((*i)++, ft_substr(line, *i - 1, 1));
}

char	*first_line_exp(t_minishell *data, char *line)
{
	bool	squote;
	int		i;
	char	*result;
	char	*tmp;
	char	*tmp_result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	tmp = NULL;
	squote = 0;
	i = 0;
	while (line[i] != '\0')
	{
		tmp = exp_loop(data, line, &i, &squote);
		if (!tmp)
			return (free(result), NULL);
		tmp_result = ft_strjoin(result, tmp);
		free(tmp);
		tmp = NULL;
		free(result);
		result = NULL;
		result = tmp_result;
	}
	return (result);
}
