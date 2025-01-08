#include "../../inc/minishell.h"

t_extended_exec_data *mock_parser(t_minishell *data)
{
    (void)data;
    t_extended_exec_data *exec_data_cat;
    exec_data_cat = safe_malloc(sizeof(t_extended_exec_data), "mock_parser");
    //memset(&exec_data_cat, 0, sizeof(t_extended_exec_data)); // Initialize to 0
    t_extended_exec_data_init(exec_data_cat);

    t_extended_exec_data *exec_data_gr;
    exec_data_gr = safe_malloc(sizeof(t_extended_exec_data), "mock_parser");
    //memset(&exec_data_gr, 0, sizeof(t_extended_exec_data)); // Initialize to 0
    t_extended_exec_data_init(exec_data_gr);

    t_extended_exec_data *exec_data_sd;
    exec_data_sd = safe_malloc(sizeof(t_extended_exec_data), "mock_parser");
    //memset(&exec_data_sd, 0, sizeof(t_extended_exec_data)); // Initialize to 0
    t_extended_exec_data_init(exec_data_sd);

    exec_data_cat->cmd = ft_strdup("/bin/cat"); // Command to execute
    //exec_data_cat->opt = (char *[]) { "cat", NULL }; // Command options
    exec_data_cat->opt = safe_malloc(2 * sizeof(char *), "mock_parser");
    exec_data_cat->opt[0] = ft_strdup("cat");
    exec_data_cat->opt[1] = NULL;
    exec_data_cat->env = env_to_array(data->env); // Environment variables
    exec_data_cat->here_doc_terminator = ft_strdup("END");
    exec_data_cat->is_builtin = false;
    //exec_data_cat.infile = "/home/joaomigu/Documents/42Cursus/Cursus/minishell_ut/executor/input.txt";
    

    exec_data_gr->cmd = ft_strdup("/bin/grep"); // Command to execute
    exec_data_gr->opt = (char *[]) { "grep",  "Lorem", NULL }; // Command options
    exec_data_gr->env = env_to_array(data->env); // Environment variables

    exec_data_sd->cmd = ft_strdup("/bin/sed"); // Command to execute
    exec_data_sd->opt = (char *[]) { "sed",  "s/a/J/g", NULL }; // Command options
    exec_data_sd->env = env_to_array(data->env); // Environment variables
    //exec_data_sd.outfile = "/home/joaomigu/Documents/42Cursus/Cursus/minishell_ut/executor/output.txt";
    //exec_data_cat->next = exec_data_gr;
    //exec_data_gr->next = exec_data_sd;
    return (exec_data_cat);
}

