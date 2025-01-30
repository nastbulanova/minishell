#include "minishell.h"

int	ft_isspace(int c)
{
	return (c == 9 || c == 13 || c == 32);
}

int ft_iswordchar(int c)
{
	return (ft_isprint(c) && !ft_isspace(c) && c != '>' && c != '<' && c != '\'' && c != '\"' && c != '|');
}

int ft_isquote(int c)
{
	return (c == 39);
}

int ft_isdblquote(int c)
{
	return (c == 34);
}

int ft_isenvvar(int c)
{
	return (ft_isalpha(c) || ft_isalnum(c) || c == '_');
}
