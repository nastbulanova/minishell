#ifndef ENV_H
#define ENV_H

# include "defines.h"
# include "structs.h"

void env_init(char **envp, t_env **env);
void env_init_default(t_env **env);
t_env *env_extract(char *str);

//env_free
void env_free(t_env *head);

//env_aux.c
void env_add(t_env **head, t_env *new);
void env_remove(t_env **head, char *name);
void env_print(t_env *head);

//env_init.c
t_env *env_new(char *name, char *value);

#endif