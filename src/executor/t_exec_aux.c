#include "../../inc/minishell.h"



void t_extended_exec_data_free(t_extended_exec_data *commands)
{
    t_extended_exec_data *temp;
    while (commands)
    {
        temp = commands;
        commands = commands->next;
        free(temp->cmd);
        free(temp->opt);
        free(temp->env);
        free(temp->infile);
        free(temp->outfile);
        free(temp);
    }
}

void t_extended_exec_data_print(t_extended_exec_data *data, bool no_env, bool no_op)
{
    t_extended_exec_data *current = data;
    
    int i;
    while (current != NULL)
    {
        printf("Command: %s\n", current->cmd);
        
        printf("Options: ");
        if (current->opt && no_op)
        {
            i = -1;
            while (current->opt[++i])
                printf("    %s ", current->opt[i]);
        }
        else
        {
            if (!no_op)
                printf("Disable print");
            else
                printf("(null)");
        }
        printf("\n");
        printf("Environment: ");
        if (current->env && no_env)
        {
            i = -1;
            while (current->env[++i])
                printf("    %s ", current->env[i]);
        }
        else
        {
            if (!no_env)
                printf("Disable print");
            else
                printf("(null)");
        }
        printf("\n");
        printf("Pipe Input: %d\n", current->is_pipe_input);
        printf("Pipe Output: %d\n", current->is_pipe_output);
        printf("Pipe: [%d, %d]\n", current->pipe[0], current->pipe[1]);
        printf("Input File: %s\n", current->infile ? current->infile : "(null)");
        printf("Output File: %s\n", current->outfile ? current->outfile : "(null)");
        printf("Append Output: %d\n", current->append_output);
        printf("Input File FD: %d\n", current->infile_fd);
        printf("Output File FD: %d\n", current->outfile_fd);
        printf("Exit Status: %d\n", current->exit_status);
        printf("Is Builtin: %s\n", current->is_builtin ? "true" : "false");
        if (current->next != NULL)
            printf("Next: %p\n", (void*)current->next);
        else
            printf("Next: (null)\n");
        printf("----------\n");
        current = current->next;
    }
}
