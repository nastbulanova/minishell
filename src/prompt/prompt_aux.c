#include "../../inc/minishell.h"
void built_left_prompt(char *prompt, char *user, char *local)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (user[j])
    {
        prompt[i] = user[j];
        j++;
        i++;
    }
    prompt[i] = '@';
    i++;
    j = 0;
    while (local[j])
    {
        prompt[i] = local[j];
        j++;
        i++;
    }
    prompt[i] = ':';
}

static void resolve_host(char *session_manager, size_t *start_len, char **start)
{
    *start = NULL;
    *start_len = ft_strlen("local/");
    *start = ft_strnstr(session_manager, "local/", *start_len);
    if (!*start) 
    {
        *start_len = ft_strlen("unix/");
        *start = ft_strnstr(session_manager, "unix/", *start_len);
    }
    if (!*start)
        *start_len = 0;
}


char *extract_host(char *session_manager)
{
    char    *start;
    char    *end;
    size_t  start_len;
    size_t  session_len;
    char    *session;

    if (!session_manager)
        return (NULL);
    resolve_host(session_manager, &start_len, &start);
    if (!start)
        return (NULL);
    start +=start_len;
    end = ft_strchr(start, '.');
    if (!end) 
        return (NULL); 
    session_len = end - start;
    session = safe_malloc(session_len + 1, "extract_host @ prompt.c");
    ft_strlcpy(session, start, session_len);
    return (session);
}


