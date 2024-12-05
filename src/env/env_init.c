#include "../inc/minishell.h"

static int relative_length(char **split)
{
    int result;
    int split_size;
    int i;

    split_size = array_len(split);
    result = 1;
    i = 1;
    while(i < split_size - 1)
    {
        result += ft_strlen(split[i]) + 1;
        i++;
    }
    return (result);

}
static void update_shell_path(char *arg_path, t_env *env)
{
    char *pwd;
    int pwd_len;
    int relative_path_len;
    int split_size;
    char **split_relative_path;
    char *absolutepath;
    
    if (arg_path[0] == '/')
    {
        env_update(env, arg_path);
        return ;
    }
    pwd = NULL;
    pwd = getcwd(pwd, 0);
    if (!pwd)
        error_exit("getcwd returned NULL", "update_shell_path in env_init");
    pwd_len = ft_strlen(pwd);
    split_relative_path = ft_split(arg_path, '/');
    split_size = array_len(split_relative_path);
    relative_path_len = relative_length(split_relative_path);
    absolutepath = ft_calloc(1, relative_path_len + pwd_len + 1);
    int i = 0;
    while (i < pwd_len)
    {
        absolutepath[i] = pwd[i];
        i++;
    }
    i = 1;
    int j = 0;
    while (i < split_size - 1)
    {
        j = 0;
        absolutepath[pwd_len] = '/';
        pwd_len++;
        while (split_relative_path[i][j])
        {
            absolutepath[pwd_len + j] = split_relative_path[i][j];
            j++;
        }
        pwd_len += j;
        i++;
    }
    i = 0;
    while (split_relative_path[i])
    {
        free(split_relative_path[i]);
        i++;
    }
    env_update(env, absolutepath);
    free(absolutepath);
    free(split_relative_path);
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

void env_init_default(t_minishell *shell)
{
    char *pwd;
    t_env **env;

    pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
        error_exit("NULL pwd on env_init_default (env_init.c)", "env_init_default in env_init.c");
    env = &shell->env;
    env_add(env, env_create("PWD", pwd));
    env_add(env, env_create("SHLVL", "1"));
    env_add(env, env_create("_", "/usr/bin/env"));
    free(pwd);

}


