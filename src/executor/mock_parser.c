#include "../../inc/minishell.h"

t_extended_exec_data *mock_parser(char *input, t_minishell *data)
{
    (void)input;
    (void)data;
    t_extended_exec_data *head;
    // fill with commands by hand according to input or disregarding input
    //ls -l | grep txt > output.txt
    head = NULL;

    t_extended_exec_data *cmd_1;
    cmd_1 = safe_malloc(sizeof(t_extended_exec_data), "mock_parser @ mock_parser.c");
    cmd_1->cmd = ft_strdup("ls");
    cmd_1->opt = safe_malloc(2 * sizeof(char*), "mock_parser @ mock_parser.c");
    cmd_1->opt[0] = ft_strdup("-l");
    cmd_1->opt[1] = NULL;
    cmd_1->env = NULL;
    cmd_1->is_pipe_input = 0;
    cmd_1->is_pipe_output = 0; 
    pipe(cmd_1->pipe);          
    cmd_1->infile = NULL;
    cmd_1->outfile = NULL;
    cmd_1->append_output = 0;
    cmd_1->infile_fd = -1;
    cmd_1->outfile_fd = -1;
    cmd_1->exit_status = 0;
    cmd_1->is_builtin = 0;
    cmd_1->next = NULL;
    

    head =cmd_1;
    return head;
}

void execute_commands(t_extended_exec_data *commands, t_minishell *data)
{
    (void)data;
    t_extended_exec_data *current = commands;

    while (current)
    {
        // Execute each command (handle pipes, redirections, etc.)
        //execute_single_command(current, data);
        t_extended_exec_data_print(current, true, false);
        current = current->next;
    }
}
