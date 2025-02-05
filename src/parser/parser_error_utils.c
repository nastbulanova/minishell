#include "../../inc/minishell.h"

t_parser_error syntax_error(t_minishell **data, t_token **token)
{
    write(2, "minishell: syntax error near unexpected token `", 47);
    if ((*token)->next)
    {
        *token = (*token)->next;
        write(2, (*token)->start, (*token)->len);
    }
    else
        write(2, "\\n", 2);
    write(2, "'\n", 2);
    free_exec_data((*data)->exec_data);
    free_parser_data(data);
    return (SYNTAX_ERROR);
}

t_parser_error memory_error(t_minishell **data)
{
    write(2, "minishell: memory allocation failed\n", 37);
    free_exec_data((*data)->exec_data);
    free_parser_data(data);
    return (MALLOC_ERROR);
}
