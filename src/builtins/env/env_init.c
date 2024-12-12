#include "../../../inc/minishell.h"


char **sanitize_arg_path(char **split_arg_path)
{
    int sanitized_size;
    char **new_split;
    int i;
    int index;

    sanitized_size = 0;
    i = -1;
    while (split_arg_path[++i])
    {
        if ((c_strcmp(split_arg_path[i], "..") != 0) && (c_strcmp(split_arg_path[i], ".") != 0))
            sanitized_size++;
    }
    new_split = safe_malloc((sanitized_size + 1) * sizeof(char *), "sanitized_arg_path @ env/env_init.c");
    i = -1;
    index = 0;
    while (split_arg_path[++i])
    {
        if ((c_strcmp(split_arg_path[i], "..") != 0) && (c_strcmp(split_arg_path[i], ".") != 0))
        {
            new_split[index] = ft_strdup(split_arg_path[i]);
            index++;
        }
    }
    free_array(split_arg_path);
    return(new_split);
}

char *final_path_one(char **sanitized_arg_path, char *pwd)
{
    char *final_path;
    char **split_pwd;

    final_path = NULL;
    if (c_strcmp(sanitized_arg_path[0], "home") == 0)
        final_path = get_path_from_single_array(sanitized_arg_path);
    else
    {
        split_pwd = ft_split(pwd, '/');
        final_path = get_path_from_arrays(split_pwd, sanitized_arg_path);
        free_array(split_pwd);
    }
    return (final_path);
}
static void update_shell_path(char *arg_path, t_env *env)
{
    (void)env;
    char **sanitized_arg_path;
    char *final_path;
    char *pwd;

    pwd = NULL;
    sanitized_arg_path = NULL;
    pwd = getcwd(pwd, 0);
    if (!pwd)
        error_exit("error on getcwd", "final_path_two @ env_init");
    if (arg_path && arg_path[0] != '\0')
    {
        sanitized_arg_path = sanitize_arg_path(ft_split(arg_path, '/'));
        final_path = final_path_one(sanitized_arg_path, pwd);
        free_array(sanitized_arg_path);
    }
    else
        final_path = ft_strdup(pwd);
    env_update(env, final_path);
    free(pwd);
    free(final_path);
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

