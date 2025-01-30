#include "minishell.h"

void    free_redirs(t_redir **redirs)
{
	t_redir *curr;
    t_redir *next;

    curr = *redirs;
    while (curr)
    {
        next = curr->next;
        free(curr->str);
        free(curr);
        curr = next;
    }
    *redirs = NULL;
}

void    free_opt_llist(t_opt_llist **opt_llist)
{
	t_opt_llist *curr;
    t_opt_llist *next;

    curr = *opt_llist;
    while (curr)
    {
        next = curr->next;
        if (curr->opt)
            free(curr->opt);
        free(curr);
        curr = next;
    }
    *opt_llist = NULL;
}

void    free_exec_data(t_exec_data *tmp_exec_data)
{
	if (tmp_exec_data->cmd)
	{
		free(tmp_exec_data->cmd);
		tmp_exec_data->cmd = NULL;
	}
	free_opt_llist(&(tmp_exec_data->opt_llist));
	free_redirs(&(tmp_exec_data->redirs));
	if (tmp_exec_data->opt)
	{
		free_array(tmp_exec_data->opt);
		tmp_exec_data->opt = NULL;
	}
	free(tmp_exec_data);
	tmp_exec_data = NULL;
}

void free_parser_data(t_minishell ***data)
{
	t_token *tmp_token;
	t_exec_data *tmp_exec_data;

	while ((**data)->list_exec_data)
	{
		tmp_exec_data = (**data)->list_exec_data;
		(**data)->list_exec_data = (**data)->list_exec_data->next;
		free_exec_data(tmp_exec_data);
		tmp_exec_data = NULL;
	}
	(**data)->list_exec_data = NULL;
	while ((**data)->token_head)
	{
		tmp_token = (**data)->token_head;
		(**data)->token_head = (**data)->token_head->next;
		free(tmp_token->start);
		tmp_token->start = NULL;
		free(tmp_token);
		tmp_token = NULL;
	}
	(**data)->token_head = NULL;
}
