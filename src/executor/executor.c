#include "../../inc/minishell.h"


void init_cmd(t_exec_data *exec_data)
{
    exec_data->cmd = NULL;
    exec_data->opt = NULL;
    exec_data->is_builtin = false;
    exec_data->redirs = NULL;
    exec_data->exit_status = 0;
}

void process_rdirs_aux(t_redir *redirs, int *safe_fd, char **redir_error)
{
    while(redirs)
    {
        errno = 0;
        if (redirs->type != HEREDOC && redirs->type != HEREDOC_QUOTED)
        {
            if (redirs->type == INPUT)
                *safe_fd = open(redirs->str, O_RDONLY);
            else if (redirs->type == OUTPUT)
                *safe_fd = open(redirs->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            else if (redirs->type == OUTPUT_APPEND)
                *safe_fd = open(redirs->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (*safe_fd < 0)
            {
                if (!*redir_error)
                    *redir_error = strdup(strerror(errno));
                if (errno == 13)
                    break;
            }
            if (*safe_fd >= 0)
                close(*safe_fd);
        }
        redirs = redirs->next;
    }
}
void process_rdirs(t_exec_data *current, char **redir_error)
{
    int safe_fd;

    while (current)
    {
        process_rdirs_aux(current->redirs, &safe_fd, redir_error);
        current = current->next;
    }
}

void add_previous(t_exec_data **head, t_exec_data new)
{
    if (!*head)
    {
        *head = &new;
        new.next = NULL;
        return;
    };
    new.next = *head; // Point the new node to the current head
    *head = &new;
}
void execute_command(t_exec_data *head, char **envp)
{
    t_exec_data *current = head;
   
    int pid[3];
    int original_fd = dup(STDIN_FILENO);;
    int prev_fd = dup(STDIN_FILENO);
    fprintf(stderr, "Starting Prev_fd[%d]\n",  prev_fd);
    int count = 0;
    //(void)previous;
    while (current)
    {
        if (current->next)
            pipe(current->pipe);
        //if (!init_pipe(current->pipe))
        //    break;
        pid[count] = fork();
        if (pid[count] == 0)
        {
            if(dup2(prev_fd, STDIN_FILENO) == -1)
            {
                fprintf(stderr, "erro on dup 2 STDIN\n");
            }
            if (current->next)
            {
                if(dup2(current->pipe[1], STDOUT_FILENO) == -1)
                {
                    fprintf(stderr, "erro on dup 2 STDOUT (%d)\n", STDOUT_FILENO);
                }
                close(current->pipe[0]);
            }
            fprintf(stderr, "Current CMD: %s CPipe[%d][%d] Prev_fd[%d]\n", current->cmd, current->pipe[0], current->pipe[1], prev_fd);
            if (execve(current->cmd, current->opt, envp) == -1)
            {
                perror("execve failed");
                perror(strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
        else
        {
           
            close(current->pipe[1]);
            close(prev_fd);
            prev_fd = current->pipe[0];
        }
        count++;
        current = current->next;
    }
    int i = -1;
    while (++i <= count)
        waitpid(pid[i], NULL, 0);
    dup2(original_fd, STDIN_FILENO);
}
