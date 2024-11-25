#include "../inc/env.h"


static char *env_name_extract(char *str)
{
    char *name;
    int i;

    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    name = calloc(i + 1, sizeof(char));
    if (!name)
        return (NULL);
    i = 0;
    while(str[i] && str[i] != '=')
    {
        name[i] = str[i];
        i++;
    }
    return (name);
}
static char *env_value_extract(char *str)
{
    int string_len; 
    int i;
    int j;
    char *value;

    string_len = ft_strlen(str);
    i = 0;
    while(str[i] && str[i] != '=')
        i++;
    value = ft_calloc(string_len - i, sizeof(char));
    if (!value)
        return (NULL);
    i++;
    j = 0;
    while(str[i])
        value[j++] = str[i++];
    return (value);
}
t_env *env_extract(char *str)
{
    char *equal_pos;
    t_env *result;

    equal_pos = ft_strchr(str, '=');
    if (equal_pos == NULL || equal_pos == str)
        return (NULL);
    result = ft_calloc(1, sizeof(t_env));
    if (!result)
        return (NULL);
    result->name = env_name_extract(str);
    result->value = env_value_extract(str);
   
    return (result);
}
void env_init(char **envp, t_env **env)
{
    int i;
    t_env *new;

    i = 0;
    while(envp[i])
    {
        new = env_extract(envp[i]);
        if (new)
            env_add(env, new);
        i++;
    }
}

