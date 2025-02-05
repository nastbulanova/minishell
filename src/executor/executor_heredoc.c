#include "../../inc/minishell.h"

static bool is_last_heredoc(t_redir *redir)
{
    if (!redir)
        return (true);

    while (redir)
    {
        if (redir->type == HEREDOC || redir->type == HEREDOC_QUOTED)
            return (false);
        redir = redir->next;
    }
    return (true);
}

static bool break_loop(t_redir *current, char *input, bool last_input, int fd)
{
    if (!input) 
    {
        if (current->str && current->str[0] == '\0')
            return (true); 
        if (last_input)
            write(fd, "\n", 1);
        return (true);
    }
    if (c_strcmp(input, current->str) == 0)
        return (true);
    if (last_input)
    {
        write(fd, input, strlen(input));
        write(fd, "\n", 1);
    }
   return (false);
}

void heredoc_loop(t_redir *current, int fd)
{
    char * input;
    bool last_input;
    int (*default_getc_function)(FILE *);

    if (!current)
        return ;
    last_input = is_last_heredoc(current->next); 
    set_state_signal_handlers(HERE_DOC);
    default_getc_function = rl_getc_function;
    rl_getc_function = getc;
    while (true)
    {
        input = readline("> ");
        if (break_loop(current, input, last_input, fd))
            break;  
        free(input);
    }
    if (input)
        free(input);
    rl_getc_function = default_getc_function;
    set_state_signal_handlers(MAIN);
}
