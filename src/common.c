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
void minishell_exit(char *msg, t_minishell *data)
{
    int exit_status;

    exit_status = data->exit_code;
    if (msg)
        ft_putstr_fd(msg, STDOUT_FILENO);
    minishell_free(data);
    exit((unsigned char)exit_status);
}
/*
void minishell_prompt(t_minishell *data)
{
    char *pwd;
    char *final_prompt;
    t_env *user_name;
    t_env *hostname;
    pwd = NULL;
    if (data->prompt)
        free(data->prompt);
    pwd = getcwd(pwd, 0);
    user_name = env_retrieve(data->env, "USER");
    hostname = env_retrieve(data->env, "SESSION_MANAGER");
}
*/