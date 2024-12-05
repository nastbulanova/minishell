#include "../inc/minishell.h"
int custom_strcmp(char *str_one, char *str_two)
{
    size_t str_one_len;
    size_t str_two_len;
    size_t big;
    if (!str_one && !str_two)
        return (0);
    if (!str_one || !str_two)
        return (1);
    str_one_len = ft_strlen(str_one);
    str_two_len = ft_strlen(str_two);
    if (str_one_len >= str_two_len)
        big = str_one_len;
    else
        big = str_two_len;
    return (ft_strncmp(str_one, str_two, big));

}

void sync_export_list(t_minishell *data)
{
    t_env       *env;
    t_env       *exp;

    env = data->env;
    if (!env)
        return;
    while (env)
    {
        exp = env_retrieve(data->env, env->name);
        if (exp)
        {
            ft_printf("Exp Found: %s %s %s %d\n", exp->name, exp->value, env->value, custom_strcmp(exp->value, env->value));
            if (exp->value && env->value && custom_strcmp(exp->value, env->value) != 0)
            {
                ft_printf("Updated %s exp valur %s new_value %s\n", exp->name, exp->value, env->value);
                env_update(exp, env->value);
            }
            else if (!exp->value && env->value)
            {
                ft_printf("Updated %s exp valur %s new_value %s\n", exp->name, exp->value, env->value);
                env_update(exp, env->value);
            }
        }
        env = env->next;
    }
}
void sort_export_list(t_env **head)
{
    t_env *current;
    t_env temp;
    char *value_tmp;
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
            if (custom_strcmp(current->name, current->next->name) > 0)
            {
                temp.name = current->name;
                value_tmp = current->value;
                temp.visible = current->visible;
                current->name = current->next->name;
                current->value = current->next->value;
                current->visible = current->next->visible;
                current->next->name = temp.name;
                current->next->value = value_tmp;
                current->next->visible = temp.visible;
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

    head = data->exp;
    if (!head)
        return ;
    sync_export_list(data);
    sort_export_list(&head);
    while (head)
    {
        if (!head->name)
            ft_printf("Print NULL head found\n");
        if (head->name && head->value && head->visible)
            printf("declare -x %s=\"%s\"\n", head->name, head->value);
        else if (!head->value)
            printf("declare -x %s\n", head->name);
           
        head = head->next;
    }
}


