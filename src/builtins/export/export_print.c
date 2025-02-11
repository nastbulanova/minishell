/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:55:53 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/10 13:56:06 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

static void	sort_export_list_aux(t_env *current)
{
	char	*value_tmp;
	t_env	temp;

	temp.name = current->name;
	value_tmp = current->value;
	current->name = current->next->name;
	current->value = current->next->value;
	current->next->name = temp.name;
	current->next->value = value_tmp;
}

static void	sort_export_list(t_env **head)
{
	t_env	*current;
	int		swapped;

	if (!head || !*head)
		return ;
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
			break ;
	}
}

static t_env	*copy_export(t_env *original)
{
	t_env	*copy;
	t_env	*new_node;

	copy = NULL;
	new_node = NULL;
	while (original)
	{
		new_node = env_create(original->name, original->value);
		new_node->next = NULL;
		env_add(&copy, new_node);
		original = original->next;
	}
	return (copy);
}

void	exp_print(t_minishell *data)
{
	t_env	*head;
	t_env	*temp;

	head = copy_export(data->env);
	if (!head)
		return ;
	temp = head;
	sort_export_list(&head);
	while (head)
	{
		if (head->name)
		{
			if (head->value)
				printf("declare -x %s=\"%s\"\n", head->name, head->value);
			else if (!head->value)
				printf("declare -x %s\n", head->name);
		}
		head = head->next;
	}
	env_free(temp);
}
