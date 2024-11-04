#include "../../inc/minishell.h"

t_token	*token_head_init(t_token *token_head)
{
	token_head->start = 0;
	token_head->len = -1;
	token_head->type = 0;
	token_head->next = NULL;
	token_head->prev = NULL;
	return(token_head);
}

t_token *token_create(t_token *head, char *start, int len, int type)
{
	t_token	*current;
	t_token	*last;

	if (head->len == -1)
	{
		head->start = start;
		head->len = len;
		head->type = type;
		head->next = NULL;
		head->prev = NULL;
		//print_token(head);//////////////////////
		return(head);
	}
	current = head;
	while (current->next)
		current = current->next;
	last = (t_token *)malloc(sizeof(t_token));
	/*if (!tmp)
		error*/
	last->start = start;
	last->len = len;
	last->type = type;
	last->next = NULL;
	last->prev = current;
	current->next = last;
	//print_token(last);////////////////////////
	return (head);
}