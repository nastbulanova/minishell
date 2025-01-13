#include "../../inc/minishell.h"


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
    if (strcmp(input, current->str) == 0)
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

    if (!current)
        return ;
    last_input = is_last_input(current);  
    while (true)
    {
        input = readline("> ");
        if (break_loop(current, input, last_input, fd))
            break;
        free(input);
    }
    if (input)
        free(input);
    if (last_input)
        close(fd);
}
