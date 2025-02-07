#include "../../../inc/minishell.h"
char *built_exit_string(const char* str)
{
    size_t final_length;
    size_t str_length;
    char template[] = "minishell: exit: : numeric argument required\n";
    char *result;
    size_t template_index;
    size_t str_index;
    if (str)
        str_length = ft_strlen(str);
    else
        str_length = 0;
    final_length = str_length + sizeof(template);
    result = safe_malloc(final_length);
    template_index = -1;
    str_index = -1;
    while (++template_index < 17)
        result[template_index] = template[template_index];
    while (++str_index < str_length)
        result[template_index + str_index] = str[str_index];
    while (template_index + str_index < final_length)
    {
        result[template_index + str_index] = template[template_index];
        template_index++;
    }
    return (result);
}

static void check_sign(const char *str, int *index, int *sign)
{
	*sign = 1;
	*index = 0;
	if (str[*index] == '-' || str[*index] == '+')
	{
		if (str[*index] == '-')
			*sign = -1;	
		(*index)++;
	}
}

static void ft_exit_atoi_aux(char *str)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	minishell_exit(built_exit_string(str), 2, STDERR_FILENO, true);
}
char ft_exit_atoi(char *str)
{
	int sign;
	int digit;
	int index;
	long long value;

	check_sign(str, &index, &sign);
	value = 0;
	while (ft_isdigit(str[index])) 
	{
    	digit = str[index] - '0';
		if (sign < 0 && (INT64_MAX - (value * 10) < digit - 1))
		{
			ft_exit_atoi_aux(str);
			return (2);
		}
		else if (sign > 0 && (INT64_MAX - (value * 10) < digit))
		{
			ft_exit_atoi_aux(str);
			return (2);
		}
        value = (value * 10) + (digit);	
        index++;
    }
	value = value * sign;
	return ((unsigned char)value);
}




