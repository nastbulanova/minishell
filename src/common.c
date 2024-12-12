#include "../inc/minishell.h"
void print_array(char **arr)
{
    int i;
    i = -1;
    while (arr[++i])
        ft_printf("'%s'\n", arr[i]);
}

void free_array(char **arr)
{
    int i;

    i = -1;
    if (arr)
    {
        while (arr[++i])
            free(arr[i]);
        free(arr);
    }
}
int c_strcmp(char *str_one, char *str_two)
{
    if (!str_one && !str_two)
        return (1);
    if (!str_one || !str_two)
    {
        if (str_one)
            return (1);
        if (str_two)
            return (-1);
    }
    return (ft_strncmp(str_one, str_two, SIZE_MAX));
}