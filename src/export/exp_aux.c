#include "../../inc/minishell.h"

static void sort_export_list_aux(t_env *current)
{
    char *value_tmp;
    t_env temp;

    temp.name = current->name;
    value_tmp = current->value;
    temp.visible = current->visible;
    current->name = current->next->name;
    current->value = current->next->value;
    current->visible = current->next->visible;
    current->next->name = temp.name;
    current->next->value = value_tmp;
    current->next->visible = temp.visible;
}
void sort_export_list(t_env **head)
{
    t_env *current;
    int  swapped;

    if (!head || !*head)
        return;
    current = *head;
    while (true)
    {   
        swapped = 0;
        current = *head;
        while (current->next)
        {
            if (c_strcmp(current->name, current->next->name) > 0)
            {
                sort_export_list_aux(current);
                swapped++;
            }
            current = current->next;
        }
        if (swapped == 0)
            break;
    }
}
void exp_print(t_minishell *data)
{
    t_env   *head;
    t_env   *temp;

    head = copy_export(data->env);
    if (!head)
        return ;
    temp = head;
    sort_export_list(&head);
    while (head)
    {
        if (head->name)
        {
            if (head->value && head->visible)
                printf("declare -x %s=\"%s\"\n", head->name, head->value);
            else if (!head->value)
                printf("declare -x %s\n", head->name);
        }
        head = head->next;
    }
    env_free(temp);
}

t_env *copy_export(t_env *original)
{
    t_env *copy = NULL;
    t_env *new_node = NULL;

    while (original)
    {
        new_node = env_create(original->name, original->value);
        new_node->visible = original->visible;
        new_node->next = NULL;
        env_add(&copy, new_node);
        original = original->next;
    }
    return (copy);
}

