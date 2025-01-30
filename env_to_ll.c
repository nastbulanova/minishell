#include "minishell.h"

t_env *create_node(const char *name, const char *value)
{
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
        return NULL;
    new_node->name = strdup(name);
    if (!new_node->name)
    {
        free(new_node);
        return NULL;
    }
    new_node->value = strdup(value);
    if (!new_node->value)
    {
        free(new_node->name);
        free(new_node);
        return NULL;
    }
    new_node->next = NULL;
    return new_node;
}

int parse_env_var(const char *env_var, char **name, char **value)
{
    char *delimiter = strchr(env_var, '=');
    if (!delimiter)
        return -1; 

    size_t name_len = delimiter - env_var;
    *name = strndup(env_var, name_len);
    if (!*name)
        return -1; 
    *value = strdup(delimiter + 1);
    if (!*value)
    {
        free(*name);
        return -1; 
    }

    return 0;
}

t_env *env_to_linked_list(char **env)
{
    t_env *head = NULL;
    t_env *current = NULL;

    for (int i = 0; env[i] != NULL; i++)
    {
        char *name = NULL;
        char *value = NULL;

        if (parse_env_var(env[i], &name, &value) == 0)
        {
            t_env *new_node = create_node(name, value);
            free(name);
            free(value);
            
            if (!new_node)
            {
                perror("Failed to allocate memory for new node");
                return NULL;
            }

            if (!head)
                head = new_node;
            else
                current->next = new_node;

            current = new_node;
        }
        else
        {
            if (name)
                free(name);
            if (value)
                free(value);
        }
    }

    return head;
}

