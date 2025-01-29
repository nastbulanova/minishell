#include "../../inc/minishell.h"

void free_redir(t_redir *redirs)
{
    t_redir *tmp;

    while (redirs)
    {
        tmp = redirs;
        redirs = redirs->next;
        free(tmp->str);
        if (tmp->error)
            free(tmp->error);
        free(tmp);
    }
}

void free_opt_llist(t_opt_llist *opt_llist)
{
    t_opt_llist *tmp;

    while (opt_llist)
    {
        tmp = opt_llist;
        opt_llist = opt_llist->next;
        free(tmp->opt);
        free(tmp);
    }
}

void free_exec_data_list(t_exec_data *head)
{
    t_exec_data *tmp;
    int i;

    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->cmd);
        if (tmp->opt)
        {   
            i = -1;
            while (tmp->opt[++i])
                free(tmp->opt[i]);
            free(tmp->opt);
        }
        close_fd(&tmp->output_fd);
        close_fd(&tmp->input_fd);
        close_pipe(tmp->outpipe);
        free_opt_llist(tmp->opt_llist);
        free_redir(tmp->redirs);
        free(tmp);
    }
}
