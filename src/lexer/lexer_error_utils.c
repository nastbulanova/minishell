#include "../../inc/minishell.h"

void	token_clean(t_token *token_head)
{
	t_token	*tmp_token;

	while (token_head)
    {
        tmp_token = token_head;
        token_head = token_head->next;
        free(tmp_token->start);
		tmp_token->start = NULL;
        free(tmp_token);
		tmp_token = NULL;
    } 
}

t_parser_error   lexer_error(t_token *token_head, t_parser_error error)
{
	if (error == SYNTAX_ERROR)
		printf("syntax error: unclosed quote.\nI can teach you to count: one quote, two quotes, three quotes, four quotes...\n");
	else
		printf("malloc error\n");
	token_clean(token_head);
	return(error);
}