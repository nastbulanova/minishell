/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_crud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:26:47 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/26 15:56:46 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/minishell.h"

/**
 * @brief Updates the value of an environment variable.
 *
 * @param target Pointer to the environment variable to update.
 * @param new_value The new value to assign to the variable.
 *
 * If the target is NULL, the function does nothing. The old value is freed
 * before assigning the new one. If memory allocation fails for the new value,
 * the function calls error_exit.
 */
void	env_update(t_env *target, const char *new_value)
{
	if (!target)
		return ;
	if (target->value)
		free(target->value);
	if (new_value)
		target->value = ft_strdup(new_value);
	else
		target->value = NULL;
	if (!target->value && new_value)
		error_exit(RB "" RST, "env_update in env_crud.c");
}

/**
 * @brief Frees the memory allocated for an environment variable.
 *
 * @param current Pointer to the environment variable to be deleted.
 *
 * This function frees the memory for the name, value, and the structure itself.
 */
static void	delete_aux(t_env *current)
{
	if (current)
	{
		if (current->name)
			free(current->name);
		if (current->value)
			free(current->value);
		free(current);
	}
}

/**
 * @brief Deletes an environment variable from the linked list.
 *
 * @param head Pointer to the head of the environment variable list.
 * @param name The name of the variable to delete.
 *
 * If the variable is found, it is removed from the list and its memory is freed.
 * If the list is empty or the variable is not found, the function does nothing.
 */
void	env_delete(t_env **head, char *name)
{
	t_env	*current;
	t_env	*previous;

	if (!head || !*head)
		return ;
	previous = NULL;
	current = *head;
	while (current)
	{
		if (current->name && c_strcmp(current->name, name) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*head = current->next;
			delete_aux(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

/**
 * @brief Creates a new environment variable.
 *
 * @param name The name of the variable.
 * @param value The value of the variable.
 *
 * @return Pointer to the newly created environment variable.
 *
 * The function allocates memory for a new environment variable 
 * and its name/value.
 * If value is NULL, the variable is created with a NULL value.
 */
t_env	*env_create(char *name, char *value)
{
	t_env	*new;

	new = safe_malloc(sizeof(t_env));
	new->name = ft_strdup(name);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}

/**
 * @brief Retrieves an environment variable from the linked list.
 *
 * @param head Pointer to the head of the environment variable list.
 * @param name The name of the variable to retrieve.
 *
 * @return Pointer to the environment variable if found, otherwise NULL.
 */
t_env	*env_retrieve(t_env *head, char *name)
{
	if (!name || !*name)
		return (NULL);
	while (head)
	{
		if (!c_strcmp(head->name, name))
			return (head);
		head = head->next;
	}
	return (NULL);
}
