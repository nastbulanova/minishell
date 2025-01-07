#include "../../inc/minishell.h"

t_extended_exec_data *mock_parser(char *input, t_minishell *data)
{
    (void)input;
    (void)data;
    t_extended_exec_data exec_data_cat;
    memset(&exec_data_cat, 0, sizeof(t_extended_exec_data)); // Initialize to 0
    init_cmd(&exec_data_cat);
    t_extended_exec_data exec_data_gr;
    memset(&exec_data_gr, 0, sizeof(t_extended_exec_data)); // Initialize to 0
    init_cmd(&exec_data_gr);
    t_extended_exec_data exec_data_sd;
    memset(&exec_data_sd, 0, sizeof(t_extended_exec_data)); // Initialize to 0
    init_cmd(&exec_data_sd);

    exec_data_cat.cmd = "/bin/cat"; // Command to execute
    exec_data_cat.opt = (char *[]) { "cat", NULL }; // Command options
    exec_data_cat.env = data->env; // Environment variables
    exec_data_cat.here_doc_terminator = "END";
    //exec_data_cat.infile = "/home/joaomigu/Documents/42Cursus/Cursus/minishell_ut/executor/input.txt";
    

    exec_data_gr.cmd = "/bin/grep"; // Command to execute
    exec_data_gr.opt = (char *[]) { "grep",  "Lorem", NULL }; // Command options
    exec_data_gr.env = data->env; // Environment variables

    exec_data_sd.cmd = "/bin/sed"; // Command to execute
    exec_data_sd.opt = (char *[]) { "sed",  "s/a/J/g", NULL }; // Command options
    exec_data_sd.env = data->env; // Environment variables
    //exec_data_sd.outfile = "/home/joaomigu/Documents/42Cursus/Cursus/minishell_ut/executor/output.txt";
    exec_data_cat.next = &exec_data_gr;
    exec_data_gr.next = &exec_data_sd;
    return (&exec_data_cat);
}

