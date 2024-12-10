#include "../inc/minishell.h"

int relative_length(char **split)
{
    int result;
    int split_size;
    int i;

    split_size = array_size(split);
    result = 1;
    i = 1;
    while(i < split_size - 1)
    {
        result += ft_strlen(split[i]) + 1;
        i++;
    }
    return (result);

}
char *final_path(char **split_pwd, char **split_arg)
{
    int size = 0;
    int i = 0;
    char *result;
    while (split_pwd[i] && c_strcmp(split_pwd[i], split_arg[0]))
    {
        size++;
        size += ft_strlen(split_pwd[i]);
        i++;
    }
    i = 0;
    while (split_arg[i])
    {
        size++;
        size += ft_strlen(split_arg[i]);
        i++;
    }
    i = 0;
    result = safe_malloc(size + 1 * sizeof(char), "final_path @ env_init");
    //printf("Final Path Size %d\n", size + 1);
    size = 0;
    while (split_pwd[i] && c_strcmp(split_pwd[i], split_arg[0]))
    {
        int j = 0;
        result[size++] = '/';
        while (split_pwd[i][j])
            result[size++] = split_pwd[i][j++];
        i++;
    }
    i = 0;
    while (split_arg[i])
    {
        int j = 0;
        result[size++] = '/';
        while (split_arg[i][j])
            result[size++] = split_arg[i][j++];
        i++;
    }
    return (result);
}
static void update_shell_path(char *arg_path, t_env *env)
{
    //char **split_relative_path;
    char *pwd;
    //char *absolutepath;
    //int pwd_len;
    //int relative_path_len;
    //int split_size;
    
    if (arg_path[0] == '/')
    {
        env_update(env, arg_path);
        return ;
    }
    else if (arg_path[0] == '.')
    {
        while (*arg_path == '.')
        {
            if (*(arg_path + 2) && *(arg_path + 2) )
            arg_path++;
        }
    }
    pwd = NULL;
    pwd = getcwd(pwd, 0);
    if (!pwd)
        error_exit("getcwd returned NULL", "update_shell_path in env_init");
    
    printf("pwd : %s\n", pwd);
    printf("arg_path : %s\n", arg_path);
    char **split_pwd = ft_split(pwd, '/');
    char **split_arg = ft_split(arg_path, '/');
    {
        if (!c_strcmp(split_arg[0], "home"))
        {
             printf("Final Path (split_arg[0]): %s\n", arg_path);
        }
        else if (!c_strcmp(split_pwd[0], "home"))
        {
            char *absolute_path = final_path(split_pwd, split_arg);
            printf("Final Path (absolute_path): %s\n", absolute_path);
        }
    }
    //int size = array_size(split_pwd);

    //env_update(env, absolutepath);
    //free(absolutepath);
    //free(split_relative_path);
    free(pwd);
}

void env_init(char **argv, char **envp, t_minishell *shell)
{
    int i;
    t_env *new;
    t_env *name_shell;
    t_env **head;

    head = &shell->env;
    i = 0;
    while(envp[i])
    {
        new = env_extract(envp[i]);
        if (new)
            env_add(head, new);
        i++;
    }
    name_shell = env_retrieve(*head, "SHELL");
    if (name_shell)
        update_shell_path(argv[0], name_shell);
}

void env_init_default(t_minishell *data)
{
    char *pwd;
    t_env **env;

    pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
        error_exit("NULL pwd on env_init_default (env_init.c)", "env_init_default in env_init.c");
    env = &data->env;
    env_add(env, env_create("PWD", pwd));
    env_add(env, env_create("SHLVL", "1"));
    env_add(env, env_create("_", "/usr/bin/env"));
    free(pwd);
}


