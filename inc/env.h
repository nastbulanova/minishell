#ifndef ENV_H
#define ENV_H

# include "defines.h"
# include "structs.h"

//env_init.c
void env_init(char **argv, char **envp, t_env **env);
void env_init_default(t_env **env);
t_env *env_extract(char *str);

//env_free
void env_free(t_env *head);

//env_aux.c
void env_add(t_env **head, t_env *new);
void env_print(t_env *head);

//env_crud
void env_delete(t_env **head, char *name);
t_env *env_retrieve(t_env *head, char *name);
t_env *env_create(char *name, char *value);
void env_update(t_env *target, const char *new_value);

#endif