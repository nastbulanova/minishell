#include "../../../inc/minishell.h"

static size_t get_arrays_size(char **split_pwd, char **split_arg)
{
    size_t size;
    int i;

    size = 0;
    i = 0;
    while (split_pwd[i] && c_strcmp(split_pwd[i], split_arg[0]))
    {
        size += ft_strlen(split_pwd[i]) + 1;
        i++;
    }
    i = 0;
    while (split_arg[i])
    {
        size += ft_strlen(split_arg[i]) + 1;
        i++;
    }
    return (size);
}

static void copy_arrays(char *result, char **split_pwd, char **split_arg)
{
    int i;
    int j;
    size_t size;

    i = 0;
    size = 0;
    while (split_pwd[i] && c_strcmp(split_pwd[i], split_arg[0]))
    {
        j = 0;
        result[size++] = '/';
        while (split_pwd[i][j])
            result[size++] = split_pwd[i][j++];
        i++;
    }
    i = 0;
    while (split_arg[i])
    {
        j = 0;
        result[size++] = '/';
        while (split_arg[i][j])
            result[size++] = split_arg[i][j++];
        i++;
    }
}
char *get_path_from_arrays(char **split_pwd, char **split_arg)
{
    char *result;
    
    result = safe_malloc((get_arrays_size(split_pwd, split_arg) + 1) * sizeof(char), "final_path @ env_init");
    copy_arrays(result, split_pwd, split_arg);
    return (result);
}

char *get_path_from_single_array(char **split)
{
    int i;
    int j;
    size_t size;
    char *result;

    size = 0;
    i = -1;
    while (split[++i])
        size += ft_strlen(split[i]) + 1;
    result = safe_malloc((size + 1) * sizeof(char), "get_path_from_single_array @ env_init");
    i = -1;
    while (split[++i])
    {
        size = 0;
        j = -1;
        if (i != 0)
            result[size++] = '/';
        while (split[i][++j])
        {
            result[size] = split[i][j];
            size++;
        }
    }
    return (result);
}





