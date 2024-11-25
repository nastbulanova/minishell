#ifndef ENV_H
#define ENV_H

# include "minishell.h"

void env_init(char **envp, t_env **env);
t_env *extract_env(char *str);

//env_free
void env_free(t_env *head);

//env_aux.c
void env_add(t_env **head, t_env *new);
void env_remove(t_env **head, char *name);
void env_print(t_env *head);



#endif