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
    cmd_1->env = env_to_array(data->env);
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

    int prev_pipe[2] = {-1, -1};
    while (current)
    {
        t_extended_exec_data_print(current, true, false); //DEBUG print command

        if (current->is_pipe_input)  // Read from the previous command's pipe
        {
            if (dup2(prev_pipe[0], STDIN_FILENO) == -1)
                error_exit("dup2 for pipe input", "execute_commands @ mock_parser");
            close(prev_pipe[0]);
        }
        if (current->is_pipe_output)  // Create pipe for the current command
        {
            if (pipe(current->pipe) == -1)
                error_exit("pipe failed", "execute_commands @ mock_parser");
            // Prepare to write to the pipe
            if (dup2(current->pipe[1], STDOUT_FILENO) == -1)
                error_exit("dup2 for pipe output", "execute_commands @ mock_parser");
        }
        // Handle redirection
        if (current->infile)  // Input redirection (e.g., < input.txt)
        {
            int infile_fd = open(current->infile, O_RDONLY);
            if (infile_fd == -1)
                error_exit("open infile", "execute_commands @ mock_parser");
            if (dup2(infile_fd, STDIN_FILENO) == -1)
                 error_exit("dup2 input redirection", "execute_commands @ mock_parser");
            close(infile_fd);
        }
        //Execute each command (handle pipes, redirections, etc.)
        //execute_single_command(current, data);
        current = current->next;
    }
}
