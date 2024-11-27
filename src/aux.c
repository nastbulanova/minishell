#include "../inc/minishell.h"
# include "../inc/builtins.h"
# include "../inc/env.h"

void *safe_malloc(size_t bytes, const char *function_name)
{
    void *ret;

    ret = malloc(bytes);
    if (!ret)
        error_exit("Error on memory allocation", function_name);
    ft_memset(ret,0,bytes);
    return (ret);
}

void error_exit(const char *error, const char *function_name)
{
    ft_printf(RB "%s (%s)\n" RST, error, function_name);
    exit(EXIT_FAILURE);
}