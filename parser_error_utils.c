#include "minishell.h"

int syntax_error(t_minishell **data, t_token **token)
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
    free_parser_data(&data);
    return (0);
}
