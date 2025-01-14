#include "../../inc/minishell.h"

bool has_input(t_redir *redir)
{
    if (!redir)
        return (false);

    while (redir)
    {
        if (redir->type == INPUT
        || redir->type == HEREDOC
        || redir->type == HEREDOC_QUOTED)
            return (true);
        redir = redir->next;
    }
    return (false);
}

bool has_output(t_redir *redir)
{
    if (!redir)
        return (false);

    while (redir)
    {
        if (redir->type == OUTPUT || redir->type == OUTPUT_APPEND)
            return (true);
        redir = redir->next;
    }
    return (false);
}

bool is_last_output(t_redir *redir)
{
    if (!redir)
        return (false);
    redir = redir->next;

    while (redir)
    {
        if (redir->type == OUTPUT || redir->type == OUTPUT_APPEND)
            return (false);
        redir = redir->next;
    }
    return (true);
}

bool is_last_input(t_redir *redir)
{
    if (!redir)
        return (false);
    redir = redir->next;

    while (redir)
    {
        if (redir->type == INPUT || redir->type == HEREDOC
        || redir->type == HEREDOC_QUOTED)
            return (false);
        redir = redir->next;
    }
    return (true);
}

bool safe_fd_error(t_redir *temp, char* redir_error, int err_number)
{
    fprintf(stderr, "Minishell: ");
    if (redir_error)
        fprintf(stderr, "%s", redir_error);
    else
        fprintf(stderr, "%s", strerror(err_number));
    fprintf(stderr, ": %s\n", temp->str);//TODO remove the pwd from this string
    return (false);
}

bool safe_fd_error_aux(t_redir *temp, char* redir_error, int err_number)
{
    fprintf(stderr, "Minishell: %s: ", temp->str);
    if (redir_error)
        fprintf(stderr, "%s\n", redir_error);
    else
        fprintf(stderr, "%s", strerror(err_number));
    return (false); //return false to signal the caller a problem with output redirection
}

int call_builtin(t_exec_data *current)
{
    fprintf(stderr, "Calling builtin '%s'\n", current->cmd);
    if (c_strcmp("echo", current->cmd) == 0)
        return (cmd_echo(current->opt));
    else if (c_strcmp("cd", current->cmd) == 0)
         return (cmd_cd(current->opt));
    else if (c_strcmp("pwd", current->cmd) == 0)
         return (cmd_pwd());
    else if (c_strcmp("export", current->cmd) == 0)
         return (cmd_export(current->opt));
    else if (c_strcmp("env", current->cmd) == 0)
         return (cmd_env(current->opt));
    else if (c_strcmp("exit", current->cmd) == 0)
         return (cmd_exit(current->opt));
    else
        return (0);
}
