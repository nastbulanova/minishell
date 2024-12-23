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
    free_array(split_arg_path, NULL);
    return(new_split);
}

static void shlvl_init(t_env *head)
{
    t_env *lvl_shell;
    char *shell_lvl;
    int current_lvl;;

    lvl_shell = env_retrieve(head, "SHLVL");
    if (lvl_shell)
    {
        current_lvl = ft_atoi(lvl_shell->value);
        if (current_lvl < 0)
            current_lvl = 0;
        shell_lvl = ft_itoa(current_lvl + 1);
        env_update(lvl_shell, shell_lvl);
        free(shell_lvl);
    }
    else
        env_add(&head, env_create("SHLVL", "1"));
}

static void update_shell_path(char *arg_path, t_env *env, t_env *env_)
{
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
        free_array(sanitized_arg_path, NULL);
    }
    else
        final_path = ft_strdup(pwd);
    env_update(env, final_path);
    env_update(env_, final_path);
    free(pwd);
    free(final_path);
}

void env_init(char **argv, char **envp, t_minishell *data)
{
    int i;
    t_env *new;
    t_env *name_shell;
    t_env **head;

    head = &data->env;
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
        update_shell_path(argv[0], name_shell, NULL);
    shlvl_init(*head);
}

void env_init_default(char **argv, t_minishell *data)
{
    char *pwd;
    t_env *env;
    t_env *name_shell;
    t_env *name_;

    pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
        error_exit("NULL pwd on env_init_default (env_init.c)", "env_init_default in env_init.c");
    env = NULL;
    name_shell = NULL;
    name_ = NULL;
    env_add(&env, env_create("OLDPWD", NULL));
    env_add(&env, env_create("PWD", pwd));
    env_add(&env, env_create("SHLVL", "1"));
    env_add(&env, env_create("_", "/usr/bin/env"));
    update_shell_path(argv[0], name_shell, name_);
    data->env = env;
    free(pwd);
}


