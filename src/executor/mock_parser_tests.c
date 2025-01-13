#include "../../inc/minishell.h"

//char *g_project_path = "/home/joao/Documents/minishell_uta/executor";
//char *g_project_path = "/home/joaomigu/Documents/minishell_uta/executor";
char *g_project_path = "/home/joaomigu/Documents/42Cursus/Cursus/minishell";

char *build_full_path(const char *relative_path)
{
    size_t path_len = strlen(g_project_path) + strlen(relative_path) + 2; // Extra 2 for '/' and '\0'
    char *full_path = malloc(path_len);
    if (!full_path)
        return NULL; // Handle allocation failure
    snprintf(full_path, path_len, "%s/%s", g_project_path, relative_path);
    return full_path;
}

t_exec_data *test_88()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    exec_data_one->cmd = "echo";
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);


    exec_data_two->cmd = "echo";
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);
    
    add_redir_to_list(&exec_data_two->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01")));
    
    add_redir_to_list(&exec_data_two->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/invalid_permission")));
    
    exec_data_one->next = exec_data_two;
    exec_data_two = NULL;

    return exec_data_one;
}

t_exec_data *test_87()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    exec_data_one->cmd = "echo";
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);


    exec_data_two->cmd = "echo";
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);
    
    add_redir_to_list(&exec_data_two->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/invalid_permission")));
    
    
    exec_data_one->next = exec_data_two;
    exec_data_two = NULL;

    return exec_data_one;
}

t_exec_data *test_86()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    exec_data_one->cmd = "echo";
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    add_redir_to_list(&exec_data_one->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/invalid_permission")));
    add_redir_to_list(&exec_data_one->redirs, 
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01")));

    exec_data_two->cmd = "echo";
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);
    
    
    exec_data_one->next = exec_data_two;
    exec_data_two = NULL;

    return exec_data_one;
}

t_exec_data *test_85()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    exec_data_one->cmd = "echo";
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    add_redir_to_list(&exec_data_one->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/invalid_permission")));

    exec_data_two->cmd = "echo";
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);
    
    
    exec_data_one->next = exec_data_two;
    exec_data_two = NULL;

    return exec_data_one;
}

t_exec_data *test_84()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    exec_data_one->cmd = "echo";
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    add_redir_to_list(&exec_data_one->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01")));

    exec_data_two->cmd = "echo";
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);
    
    add_redir_to_list(&exec_data_two->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile02")));
    
    exec_data_one->next = exec_data_two;
    exec_data_two = NULL;

    return exec_data_one;
}

t_exec_data *test_83()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    exec_data_one->cmd = "echo";
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);


    exec_data_two->cmd = "echo";
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);
    
    add_redir_to_list(&exec_data_two->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01")));
    add_redir_to_list(&exec_data_two->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile02")));
    
    exec_data_one->next = exec_data_two;
    exec_data_two = NULL;

    return exec_data_one;
}

t_exec_data *test_82()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    exec_data_one->cmd = "echo";
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);


    exec_data_two->cmd = "echo";
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);
    
    add_redir_to_list(&exec_data_two->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01")));
    
    exec_data_one->next = exec_data_two;
    exec_data_two = NULL;

    return exec_data_one;
}

t_exec_data *test_81()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    exec_data_one->cmd = "echo";
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    add_redir_to_list(&exec_data_one->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01")));
    add_redir_to_list(&exec_data_one->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile02")));

    exec_data_two->cmd = "echo";
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);
    
    exec_data_one->next = exec_data_two;
    exec_data_two = NULL;

    return exec_data_one;
}

t_exec_data *test_80()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    exec_data_one->cmd = "echo";
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
   
    add_redir_to_list(&exec_data_one->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01")));

    exec_data_two->cmd = "echo";
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    exec_data_one->next = exec_data_two;
    exec_data_two = NULL;

    return exec_data_one;
}

t_exec_data *test_79()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    exec_data_one->cmd = "/bin/cat";
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);
   
    add_redir_to_list(&exec_data_one->redirs, 
                      create_rdir(INPUT, build_full_path("/input1.txt")));

   
    exec_data_two->cmd = "/bin/ls";
    exec_data_two->opt = add_string_to_array("ls", exec_data_two->opt);
    

    exec_data_one->next = exec_data_two;
    exec_data_two = NULL;

    return exec_data_one;
}

t_exec_data *test_78()
{
    t_exec_data *exec_data_cat = malloc(sizeof(t_exec_data));
    memset(exec_data_cat, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_cat);

    t_exec_data *exec_data_ls = malloc(sizeof(t_exec_data));
    memset(exec_data_ls, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_ls);

    exec_data_cat->cmd = "/bin/cat";
    exec_data_cat->opt = add_string_to_array("cat", exec_data_cat->opt);
    add_redir_to_list(&exec_data_cat->redirs, 
                      create_rdir(INPUT, build_full_path("/main.c")));
    add_redir_to_list(&exec_data_cat->redirs, 
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile")));
   

    // Link the commands
    exec_data_cat->next = NULL;

    return exec_data_cat;
}

t_exec_data *test_77()
{
    t_exec_data *exec_data_ls = malloc(sizeof(t_exec_data));
    memset(exec_data_ls, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_ls);

    t_exec_data *exec_data_cat = malloc(sizeof(t_exec_data));
    memset(exec_data_cat, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_cat);

    // Setup for first command: ls
    exec_data_ls->cmd = "/bin/ls";
    exec_data_ls->opt = add_string_to_array("ls", exec_data_ls->opt);
    add_redir_to_list(&exec_data_ls->redirs, 
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01")));
    add_redir_to_list(&exec_data_ls->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("test_files/invalid_permission")));
    add_redir_to_list(&exec_data_ls->redirs, 
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile02")));

    // Setup for second command: cat
    exec_data_cat->cmd = "/bin/cat";
    exec_data_cat->opt = add_string_to_array("cat", exec_data_cat->opt);
    add_redir_to_list(&exec_data_cat->redirs, 
                      create_rdir(INPUT, build_full_path("/input1.txt")));
    add_redir_to_list(&exec_data_cat->redirs, 
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile03")));

    // Link the commands
    exec_data_ls->next = exec_data_cat;
    exec_data_cat->next = NULL;

    return exec_data_ls;
}


t_exec_data *test_76()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls >>./test_files/invalid_permission >>./outfiles/outfile02 <missing)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (append) to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("test_files/invalid_permission"))); // Append to file with invalid permissions

    // Add output redirection (append) to "./outfiles/outfile02"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile02"))); // Append to file

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_75()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls <missing >>./test_files/invalid_permission >>./outfiles/outfile02)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (append) to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, build_full_path("missing"))); // Append to file with invalid permissions
    
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("test_files/invalid_permission"))); // Append to file with invalid permissions

    // Add output redirection (append) to "./outfiles/outfile02"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile02"))); // Append to file

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_74()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls >./outfiles/outfile01 >>./test_files/invalid_permission >>./outfiles/outfile02)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (overwrite) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Overwrite the file

    // Add output redirection (append) to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("test_files/invalid_permission"))); // Append to file with invalid permissions

    // Add output redirection (append) to "./outfiles/outfile02"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile02"))); // Append to file

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_73()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls >>./outfiles/outfile01 >>./test_files/invalid_permission)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (append) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01"))); // Append to file

    // Add output redirection (append) to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("test_files/invalid_permission"))); // Append to file with invalid permissions

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_72()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls >>./test_files/invalid_permission >>./outfiles/outfile01)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (append) to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("test_files/invalid_permission"))); // Append to file with invalid permissions

    // Add output redirection (append) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01"))); // Append to file

    exec_data_one->next = NULL;

    return exec_data_one;
}

t_exec_data *test_71()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls >>./test_files/invalid_permission)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (append) to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("test_files/invalid_permission"))); // Append to file with invalid permissions

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_70()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls >>./outfiles/outfile01 >>./outfiles/outfile02)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (append) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01"))); // Append to the file

    // Add output redirection (append) to "./outfiles/outfile02"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile02"))); // Append to the file

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_69()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls >./outfiles/outfile01 >>./outfiles/outfile01 >./outfiles/outfile02)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (overwrite) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Overwrite the file

    // Add output redirection (append) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01"))); // Append to the file

    // Add output redirection (overwrite) to "./outfiles/outfile02"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile02"))); // Overwrite the file

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_68()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls >./outfiles/outfile01 >>./outfiles/outfile01)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (overwrite) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Overwrite the file

    // Add output redirection (append) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01"))); // Append to the file

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_67()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls >>./outfiles/outfile01 >./outfiles/outfile01)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (append) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01"))); // Append to the file

    // Add output redirection (overwrite) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Overwrite the file

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_66()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls >>./outfiles/outfile01)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (append) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01"))); // Append to the file

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_65()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (ls >>./outfiles/outfile01)
    exec_data_one->cmd = "/bin/ls"; // Path to the ls binary
    exec_data_one->is_builtin = false; // ls is not a built-in command
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);

    // Add output redirection (append) to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT_APPEND, build_full_path("outfiles/outfile01"))); // Append to the file

    exec_data_one->next = NULL;

    return exec_data_one;
}

t_exec_data *test_64()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (cat >./outfiles/outfile01 <missing >./test_files/invalid_permission)
    exec_data_one->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_one->is_builtin = false; // cat is not a built-in command
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);

    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to file
    // Add input redirection with a missing file (invalid)
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, "missing")); // Input redirection with missing file

    // Add output redirection to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Invalid permission redirection

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_63()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (cat >./test_files/invalid_permission <missing)
    exec_data_one->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_one->is_builtin = false; // cat is not a built-in command
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);

    // Add output redirection to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Invalid permission redirection

    // Add input redirection with a missing file (invalid)
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, "missing")); // Input redirection with missing file

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_62()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (cat <missing >./test_files/invalid_permission)
    exec_data_one->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_one->is_builtin = false; // cat is not a built-in command
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);

    // Add input redirection with a missing file (invalid)
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, "missing")); // Input redirection with missing file

    // Add output redirection to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Invalid permission redirection

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_61()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (cat >./outfiles/outfile01 <missing)
    exec_data_one->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_one->is_builtin = false; // cat is not a built-in command
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);

    // Add output redirection to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to file

    // Add input redirection with a missing file (which is invalid)
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, "missing")); // Input redirection with missing file

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_60()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (cat <missing >./outfiles/outfile01)
    exec_data_one->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_one->is_builtin = false; // cat is not a built-in command
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);

    // Add input redirection for the command (missing file is invalid)
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, "missing")); // Input redirection with missing file

    // Add output redirection to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to file

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_59()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (cat >./test_files/invalid_permission <"./test_files/infile">)
    exec_data_one->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_one->is_builtin = false; // cat is not a built-in command
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);

    // Add input redirection for the command from "./test_files/infile"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, build_full_path("test_files/infile"))); // Input redirection from file

    // Add output redirection to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Invalid permission redirection

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_58()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for the command (cat <"./test_files/infile">)
    exec_data_one->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_one->is_builtin = false; // cat is not a built-in command
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);

    // Add input redirection for the command from "./test_files/infile"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, build_full_path("test_files/infile"))); // Input redirection from file

    // Add output redirection to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Invalid permission redirection

    exec_data_one->next = NULL;

    return exec_data_one;
}


t_exec_data *test_57()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command (echo hi)
    exec_data_one->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_one->is_builtin = true; // echo is a built-in command
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Setup for the second command (echo bye)
    exec_data_two->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_two->is_builtin = true; // echo is a built-in command
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    // Add output redirection for the second command to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Invalid permission redirection

    // Add output redirection for the second command to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to file

    // Connect the first command to the second command in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_56()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command (echo hi)
    exec_data_one->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_one->is_builtin = true; // echo is a built-in command
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Add output redirection for the first command to "./outfiles/outfile01"

    // Setup for the second command (echo bye)
    exec_data_two->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_two->is_builtin = true; // echo is a built-in command
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to file
    // Add output redirection for the second command to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Invalid permission redirection

    // Connect the first command to the second command in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_55()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command (echo hi)
    exec_data_one->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_one->is_builtin = true; // echo is a built-in command
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Setup for the second command (echo bye)
    exec_data_two->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_two->is_builtin = true; // echo is a built-in command
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    // Add output redirection for the second command to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Invalid permission redirection

    // Connect the first command to the second command in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_54()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command (echo hi)
    exec_data_one->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_one->is_builtin = true; // echo is a built-in command
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Add output redirection for the first command to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Invalid permission redirection

    // Add output redirection for the first command to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to file

    // Setup for the second command (echo bye)
    exec_data_two->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_two->is_builtin = true; // echo is a built-in command
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    // Connect the first command to the second command in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_53()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command (echo hi)
    exec_data_one->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_one->is_builtin = true; // echo is a built-in command
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Add output redirection for the first command to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Invalid permission redirection

    // Setup for the second command (echo bye)
    exec_data_two->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_two->is_builtin = true; // echo is a built-in command
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    // Connect the first command to the second command in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_52()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command (echo hi)
    exec_data_one->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_one->is_builtin = true; // echo is a built-in command
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Add output redirection for the first command to "./outfiles/outfile01"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to file

    // Add output redirection for the first command to "./test_files/invalid_permission"
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Invalid permission redirection

    // Setup for the second command (echo bye)
    exec_data_two->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_two->is_builtin = true; // echo is a built-in command
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    // Connect the first command to the second command in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_51()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command (echo hi)
    exec_data_one->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_one->is_builtin = true; // echo is a built-in command
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Add output redirection for the first command
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to file

    // Setup for the second command (echo bye)
    exec_data_two->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_two->is_builtin = true; // echo is a built-in command
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    // Add output redirection for the second command
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile02"))); // Output redirection to file

    // Connect the first command to the second command in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_50()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command (echo hi)
    exec_data_one->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_one->is_builtin = true; // echo is a built-in command
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Setup for the second command (echo bye)
    exec_data_two->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_two->is_builtin = true; // echo is a built-in command
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    // Add output redirections for the second command
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // First output redirection
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile02"))); // Second output redirection

    // Connect the first command to the second command in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_49()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command (echo hi)
    exec_data_one->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_one->is_builtin = true; // echo is a built-in command
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Setup for the second command (echo bye)
    exec_data_two->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_two->is_builtin = true; // echo is a built-in command
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    // Add output redirection for the second command
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to file

    // Connect the first command to the second command in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_48()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command (echo hi)
    exec_data_one->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_one->is_builtin = true; // echo is a built-in command
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Add output redirections for the first command
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // First output redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile02"))); // Second output redirection

    // Setup for the second command (echo bye)
    exec_data_two->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_two->is_builtin = true; // echo is a built-in command
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    // Connect the first command to the second command in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_47()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command (echo hi)
    exec_data_one->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_one->is_builtin = true; // echo is a built-in command
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Add output redirection for the first command
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to file

    // Setup for the second command (echo bye)
    exec_data_two->cmd = "/bin/echo"; // Path to the echo binary
    exec_data_two->is_builtin = true; // echo is a built-in command
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("bye", exec_data_two->opt);

    // Connect the first command to the second command in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_46()
{
    t_exec_data *exec_data = malloc(sizeof(t_exec_data));
    memset(exec_data, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data);

    // Setup for the command
    exec_data->cmd = "/bin/cat"; // Path to the cat binary
    exec_data->is_builtin = false; // cat is not a built-in
    exec_data->opt = add_string_to_array("cat", exec_data->opt);

    // Add input redirection
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(INPUT, build_full_path("test_files/infile"))); // Input redirection from file

    // Add output redirection
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to file

    exec_data->next = NULL; // No further commands in the pipeline
    return exec_data;
}

t_exec_data *test_45()
{
    t_exec_data *exec_data = malloc(sizeof(t_exec_data));
    memset(exec_data, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data);

    // Setup for the command
    exec_data->cmd = "/bin/ls"; // Path to the ls binary
    exec_data->is_builtin = false; // ls is not a built-in
    exec_data->opt = add_string_to_array("ls", exec_data->opt);

    // Add output redirections
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // First output redirection (invalid permission)
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Second output redirection
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Third output redirection (invalid permission)

    exec_data->next = NULL; // No further commands in the pipeline
    return exec_data;
}


t_exec_data *test_44()
{
    t_exec_data *exec_data = malloc(sizeof(t_exec_data));
    memset(exec_data, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data);

    // Setup for the command
    exec_data->cmd = "/bin/ls"; // Path to the ls binary
    exec_data->is_builtin = false; // ls is not a built-in
    exec_data->opt = add_string_to_array("ls", exec_data->opt);

    // Add output redirections
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // First output redirection
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Second output redirection (invalid permission)
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile02"))); // Third output redirection

    exec_data->next = NULL; // No further commands in the pipeline
    return exec_data;
}


t_exec_data *test_43()
{
    t_exec_data *exec_data = malloc(sizeof(t_exec_data));
    memset(exec_data, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data);

    // Setup for the command
    exec_data->cmd = "/bin/ls"; // Path to the ls binary
    exec_data->is_builtin = false; // ls is not a built-in
    exec_data->opt = add_string_to_array("ls", exec_data->opt);

    // Add output redirection
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile""1""2""3""4""5"))); // Output redirection to concatenated file name

    exec_data->next = NULL; // No further commands in the pipeline
    return exec_data;
}


t_exec_data *test_42()
{
    t_exec_data *exec_data = malloc(sizeof(t_exec_data));
    memset(exec_data, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data);

    // Setup for the command
    exec_data->cmd = "/bin/ls"; // Path to the ls binary
    exec_data->is_builtin = false; // ls is not a built-in
    exec_data->opt = add_string_to_array("ls", exec_data->opt);

    // Add output redirection
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile with spaces"))); // Output redirection to file with spaces in its name

    exec_data->next = NULL; // No further commands in the pipeline
    return exec_data;
}

t_exec_data *test_41()
{
    t_exec_data *exec_data = malloc(sizeof(t_exec_data));
    memset(exec_data, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data);

    // Setup for the command
    exec_data->cmd = "/bin/ls"; // Path to the ls binary
    exec_data->is_builtin = false; // ls is not a built-in
    exec_data->opt = add_string_to_array("ls", exec_data->opt);

    // Add output redirections
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // First output redirection
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("test_files/invalid_permission"))); // Second output redirection

    exec_data->next = NULL; // No further commands in the pipeline
    return exec_data;
}


t_exec_data *test_40()
{
    t_exec_data *exec_data = malloc(sizeof(t_exec_data));
    memset(exec_data, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data);

    // Setup for the command
    exec_data->cmd = "/bin/ls"; // Path to the ls binary
    exec_data->is_builtin = false; // ls is not a built-in
    exec_data->opt = add_string_to_array("ls", exec_data->opt);

    // Add output redirections
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // First output redirection
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile02"))); // Second output redirection

    exec_data->next = NULL; // No further commands in the pipeline
    return exec_data;
}


t_exec_data *test_39()
{
    t_exec_data *exec_data = malloc(sizeof(t_exec_data));
    memset(exec_data, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data);

    // Setup for the command
    exec_data->cmd = "echo"; // echo is a built-in command
    exec_data->is_builtin = true; // Mark as a built-in
    exec_data->opt = add_string_to_array("echo", exec_data->opt);
    exec_data->opt = add_string_to_array("hi", exec_data->opt); // Add argument "hi"
    exec_data->opt = add_string_to_array("bye", exec_data->opt); // Add argument "bye"

    // Add output redirection
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to ./outfiles/outfile01

    exec_data->next = NULL; // No further commands in the pipeline
    return exec_data;
}

t_exec_data *test_38()
{
    t_exec_data *exec_data = malloc(sizeof(t_exec_data));
    memset(exec_data, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data);

    // Setup for the command
    exec_data->cmd = "/bin/ls"; // Path to the ls binary
    exec_data->is_builtin = false; // ls is not a built-in
    exec_data->opt = add_string_to_array("ls", exec_data->opt);

    // Add output redirection
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(OUTPUT, build_full_path("outfiles/outfile01"))); // Output redirection to ./outfiles/outfile01

    exec_data->next = NULL; // No further commands in the pipeline
    return exec_data;
}


t_exec_data *test_37()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command
    exec_data_one->cmd = "echo"; // echo is a built-in command
    exec_data_one->is_builtin = true; // Mark as a built-in
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt); // Add argument "hi"

    // Add redirections for the first command
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, "123")); // First input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, "456")); // Second input redirection

    // Setup for the second command
    exec_data_two->cmd = "echo"; // echo is a built-in command
    exec_data_two->is_builtin = true; // Mark as a built-in
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("42", exec_data_two->opt); // Add argument "42"

    // Link the two commands in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}

t_exec_data *test_36()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command
    exec_data_one->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_one->is_builtin = false; // cat is not a built-in
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, "missing")); // Input redirection from a non-existent file

    // Setup for the second command
    exec_data_two->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_two->is_builtin = false; // cat is not a built-in
    exec_data_two->opt = add_string_to_array("cat", exec_data_two->opt);
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(INPUT, build_full_path("test_files/infile"))); // Input redirection from "test_files/infile"

    // Link the two commands in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_35()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command
    exec_data_one->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, "missing")); // Input redirection from a non-existent file

    // Setup for the second command
    exec_data_two->cmd = "echo"; // Path to echo (handled as a built-in)
    exec_data_two->is_builtin = true;
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("oi", exec_data_two->opt);

    // Link the two commands in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_34()
{
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two = malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for the first command
    exec_data_one->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT, "missing")); // Input redirection from a non-existent file

    // Setup for the second command
    exec_data_two->cmd = "/bin/cat"; // Path to the cat binary
    exec_data_two->is_builtin = true;
    exec_data_two->opt = add_string_to_array("cat", exec_data_two->opt);

    // Link the two commands in the pipeline
    exec_data_one->next = exec_data_two;
    exec_data_two->next = NULL;

    return exec_data_one;
}


t_exec_data *test_33()
{
    t_exec_data *exec_data = malloc(sizeof(t_exec_data));
    memset(exec_data, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data);

    // Setup for the command
    exec_data->cmd = "/bin/cat"; // Path to the cat binary
    exec_data->opt = add_string_to_array("cat", exec_data->opt);
    add_redir_to_list(&exec_data->redirs,
                      create_rdir(INPUT, "missing")); // Redirection from a non-existent file

    exec_data->next = NULL; // No further commands in the pipeline
    return exec_data;
}


t_exec_data *test_32()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two= malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for first command
    exec_data_one->cmd = "/bin/cat"; // Path to the grep binary
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));

    // Setup for second command
    exec_data_two->cmd = "echo"; 
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("oi", exec_data_two->opt);
    
    exec_data_one->next = exec_data_two; 
    exec_data_two->next = NULL;
    return exec_data_one;
}

t_exec_data *test_31()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two= malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for grep command
    exec_data_one->cmd = "/bin/cat"; // Path to the grep binary
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));

    // Setup for grep command
    exec_data_two->cmd = "/bin/grep"; // Path to the grep binary
    exec_data_two->opt = add_string_to_array("grep", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("hello", exec_data_two->opt);
    
    exec_data_one->next = exec_data_two; 
    exec_data_two->next = NULL;
    return exec_data_one;
}

t_exec_data *test_30()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two= malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for grep command
    exec_data_one->cmd = "/bin/cat"; // Path to the grep binary
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt);
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));

    // Setup for grep command
    exec_data_two->cmd = "echo"; // Path to the grep binary
    exec_data_two->is_builtin = true;
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array("hi", exec_data_two->opt);
    
    exec_data_one->next = exec_data_two; 
    exec_data_two->next = NULL;
    return exec_data_one;
}

t_exec_data *test_29()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two= malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for grep command
    exec_data_one->cmd = "echo"; // Path to the grep binary
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Setup for grep command
    exec_data_two->cmd = "/bin/cat"; // Path to the grep binary
    exec_data_two->opt = add_string_to_array("cat", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array(build_full_path("test_files/infile"), exec_data_two->opt);
    
    exec_data_one->next = exec_data_two; 
    exec_data_two->next = NULL;
    return exec_data_one;
}

t_exec_data *test_28()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two= malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for grep command
    exec_data_one->cmd = "echo"; // Path to the grep binary
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);

    // Setup for grep command
    exec_data_two->cmd = "/bin/cat"; // Path to the grep binary
    exec_data_two->opt = add_string_to_array("cat", exec_data_two->opt);
    
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));

    exec_data_one->next = exec_data_two; 
    exec_data_two->next = NULL;
    return exec_data_one;
}

t_exec_data *test_27()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two= malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for grep command
    exec_data_one->cmd = "echo"; // Path to the grep binary
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);

    // Add input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile_big")));

    // Setup for grep command
    exec_data_two->cmd = "echo"; // Path to the grep binary
    exec_data_two->opt = add_string_to_array("echo", exec_data_two->opt);
    
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));
    

    exec_data_one->next = exec_data_two; 
    exec_data_two->next = NULL;
    return exec_data_one;
}

t_exec_data *test_26()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two= malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for grep command
    exec_data_one->cmd = "echo"; // Path to the grep binary
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);

    // Add input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile_big")));

    // Setup for grep command
    exec_data_two->cmd = "/bin/cat"; // Path to the grep binary
    exec_data_two->opt = add_string_to_array("cat", exec_data_two->opt);
    exec_data_two->opt = add_string_to_array(build_full_path("test_files/infile"), exec_data_two->opt);
    

    exec_data_one->next = exec_data_two; 
    exec_data_two->next = NULL;
    return exec_data_one;
}

t_exec_data *test_25()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    t_exec_data *exec_data_two= malloc(sizeof(t_exec_data));
    memset(exec_data_two, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_two);

    // Setup for grep command
    exec_data_one->cmd = "echo"; // Path to the grep binary
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);

    // Add input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile_big")));

    // Setup for grep command
    exec_data_two->cmd = "/bin/cat"; // Path to the grep binary
    exec_data_two->opt = add_string_to_array("cat", exec_data_two->opt);

    // Add input redirection
    add_redir_to_list(&exec_data_two->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));
    

    exec_data_one->next = exec_data_two; 
    exec_data_two->next = NULL;
    return exec_data_one;
}

t_exec_data *test_24()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for grep command
    exec_data_one->cmd = "/bin/cat"; 
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt); 
    

    // Add input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));

    exec_data_one->next = NULL; // No pipeline, single command
    return exec_data_one;
}
t_exec_data *test_23()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for grep command
    exec_data_one->cmd = "echo"; // Path to the grep binary
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);

    // Add input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("missing")));
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("missing")));

    exec_data_one->next = NULL; // No pipeline, single command
    return exec_data_one;
}

t_exec_data *test_22()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for grep command
    exec_data_one->cmd = "echo"; // Path to the grep binary
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt);

    // Add input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("missing")));
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));

    exec_data_one->next = NULL; // No pipeline, single command
    return exec_data_one;
}

t_exec_data *test_21()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for grep command
    exec_data_one->cmd = "/bin/cat"; 
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt); 
    

    // Add input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("1""2""3""4""5")));

    exec_data_one->next = NULL; // No pipeline, single command
    return exec_data_one;
}

t_exec_data *test_20()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for grep command
    exec_data_one->cmd = "/bin/cat"; 
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt); 
    exec_data_one->opt = add_string_to_array(build_full_path("test_files/infile"), exec_data_one->opt); 
    

    // Add input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile_big")));

    exec_data_one->next = NULL; // No pipeline, single command
    return exec_data_one;
}

t_exec_data *test_19()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for grep command
    exec_data_one->cmd = "/bin/cat"; 
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("cat", exec_data_one->opt); 

    

    // Add input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/file name with spaces")));

    exec_data_one->next = NULL; // No pipeline, single command
    return exec_data_one;
}

t_exec_data *test_18()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for grep command
    exec_data_one->cmd = "echo"; // Path to the grep binary
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt); // Add "grep" as the command itself
    exec_data_one->opt = add_string_to_array("bonjour       42", exec_data_one->opt);   // Add "hi" as an argument

    // Add input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));

    exec_data_one->next = NULL; // No pipeline, single command
    return exec_data_one;
}

t_exec_data *test_17()
{
    t_exec_data *exec_data_grep = malloc(sizeof(t_exec_data));
    memset(exec_data_grep, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_grep);

    // Setup for grep command
    exec_data_grep->cmd = "/bin/grep"; // Path to the grep binary
    exec_data_grep->opt = add_string_to_array("grep", exec_data_grep->opt); // Add "grep" as the command itself
    exec_data_grep->opt = add_string_to_array("hi", exec_data_grep->opt);   // Add "hi" as an argument

    // Add input redirection
    add_redir_to_list(&exec_data_grep->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile_big")));
    add_redir_to_list(&exec_data_grep->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));

    exec_data_grep->next = NULL; // No pipeline, single command
    return exec_data_grep;
}

t_exec_data *test_16()
{
    t_exec_data *exec_data_one= malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);

    // Setup for grep command
    exec_data_one->cmd = "echo"; // Path to the grep binary
    exec_data_one->is_builtin = true;
    exec_data_one->opt = add_string_to_array("echo", exec_data_one->opt); // Add "grep" as the command itself
    exec_data_one->opt = add_string_to_array("hi", exec_data_one->opt);   // Add "hi" as an argument
    exec_data_one->opt = add_string_to_array("bye", exec_data_one->opt);
    exec_data_one->opt = add_string_to_array("bye", exec_data_one->opt);
    // Add input redirection
    add_redir_to_list(&exec_data_one->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));

    exec_data_one->next = NULL; // No pipeline, single command
    return exec_data_one;
}

t_exec_data *test_15()
{
    t_exec_data *exec_data_grep = malloc(sizeof(t_exec_data));
    memset(exec_data_grep, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_grep);

    // Setup for grep command
    exec_data_grep->cmd = "/bin/grep"; // Path to the grep binary
    exec_data_grep->opt = add_string_to_array("grep", exec_data_grep->opt); // Add "grep" as the command itself
    exec_data_grep->opt = add_string_to_array("hi", exec_data_grep->opt);   // Add "hi" as an argument

    // Add input redirection
    add_redir_to_list(&exec_data_grep->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));
    add_redir_to_list(&exec_data_grep->redirs,
                      create_rdir(INPUT,build_full_path("<infile")));

    exec_data_grep->next = NULL; // No pipeline, single command
    return exec_data_grep;
}

t_exec_data *test_14()
{
    t_exec_data *exec_data_grep = malloc(sizeof(t_exec_data));
    memset(exec_data_grep, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_grep);

    // Setup for grep command
    exec_data_grep->cmd = "/bin/grep"; // Path to the grep binary
    exec_data_grep->opt = add_string_to_array("grep", exec_data_grep->opt); // Add "grep" as the command itself
    exec_data_grep->opt = add_string_to_array("hi", exec_data_grep->opt);   // Add "hi" as an argument

    // Add input redirection
    add_redir_to_list(&exec_data_grep->redirs,
                      create_rdir(INPUT,build_full_path("test_files/infile")));

    exec_data_grep->next = NULL; // No pipeline, single command
    return exec_data_grep;
}

t_exec_data *test_13()
{
    t_exec_data *exec_data_cat = malloc(sizeof(t_exec_data));
    memset(exec_data_cat, 0, sizeof(t_exec_data));
    init_cmd(exec_data_cat);

    exec_data_cat->cmd = "/bin/cat";
    exec_data_cat->opt = add_string_to_array("cat", exec_data_cat->opt);

    // Add input redirection for "missing"
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(INPUT, build_full_path("missing")));

    // Add input redirection for "inf"
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(INPUT, build_full_path("inf")));

    // Add heredoc for "EOF"
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(HEREDOC, "EOF"));

    // Add heredoc for "/bin/ll"
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(HEREDOC, "ll"));

    exec_data_cat->next = NULL;

    return (exec_data_cat);
}

t_exec_data *test_12()
{
    t_exec_data *exec_data_cat = malloc(sizeof(t_exec_data));
    memset(exec_data_cat, 0, sizeof(t_exec_data));
    init_cmd(exec_data_cat);

    exec_data_cat->cmd = "/bin/cat";
    exec_data_cat->opt = add_string_to_array("cat", exec_data_cat->opt);

    // Add heredoc
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(HEREDOC, ""));

    // Add output redirection with append
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(OUTPUT_APPEND, build_full_path("output.txt")));

    // Add input redirection
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(INPUT, build_full_path("input.txt")));

    exec_data_cat->next = NULL;

    return (exec_data_cat);
}

t_exec_data *test_11()
{
    t_exec_data *exec_data_cat = malloc(sizeof(t_exec_data));
    memset(exec_data_cat, 0, sizeof(t_exec_data));
    init_cmd(exec_data_cat);

    exec_data_cat->cmd = "/bin/cat";
    exec_data_cat->opt = add_string_to_array("cat", exec_data_cat->opt);

    // Add heredoc
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(HEREDOC, ""));

    // Add input redirection
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(INPUT, build_full_path("input.txt")));

    exec_data_cat->next = NULL;

    return (exec_data_cat);
}

t_exec_data *test_10()
{
    ft_printf("Running test 10: cat | cat | ls \n");
    t_exec_data *exec_data_cat1 = malloc(sizeof(t_exec_data));
    memset(exec_data_cat1, 0, sizeof(t_exec_data));
    init_cmd(exec_data_cat1);
    exec_data_cat1->cmd = ft_strdup("/bin/cat");
    exec_data_cat1->opt = add_string_to_array("cat", exec_data_cat1->opt);
    

    // Second "cat" command
    t_exec_data *exec_data_cat2 = malloc(sizeof(t_exec_data));
    memset(exec_data_cat2, 0, sizeof(t_exec_data));
    init_cmd(exec_data_cat2);
    exec_data_cat2->cmd = ft_strdup("/bin/cat");
    exec_data_cat2->opt = add_string_to_array("cat", exec_data_cat2->opt);

    // "ls" command
    t_exec_data *exec_data_ls = malloc(sizeof(t_exec_data));
    memset(exec_data_ls, 0, sizeof(t_exec_data));
    init_cmd(exec_data_ls);
    exec_data_ls->cmd = ft_strdup("/bin/ls");
    exec_data_ls->opt = add_string_to_array("ls", exec_data_ls->opt);

    // Linking the commands
    exec_data_cat1->next = exec_data_cat2;
    exec_data_cat2->next = exec_data_ls;
    exec_data_ls->next = NULL;

    return (exec_data_cat1);
}

t_exec_data *test_9()
{
    ft_printf("Running test 9: ll > test_output/output.txt  | wc -l \n");
    t_exec_data *exec_data_ls = malloc(sizeof(t_exec_data));
    memset(exec_data_ls, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_ls);

    // Setup for ls command
    exec_data_ls->cmd = ft_strdup("/bin/ll"); // Command to execute
    exec_data_ls->opt = add_string_to_array("ll", exec_data_ls->opt);
    add_redir_to_list(&exec_data_ls->redirs, create_rdir(OUTPUT, build_full_path("test_output/output.txt")));

    t_exec_data *exec_data_wc = malloc(sizeof(t_exec_data));
    memset(exec_data_wc, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_wc);

    exec_data_wc->cmd = ft_strdup("/usr/bin/wc"); // Command to execute
    exec_data_wc->opt = add_string_to_array("wc", exec_data_wc->opt);
    exec_data_wc->opt = add_string_to_array("-l", exec_data_wc->opt);

    exec_data_ls->next = exec_data_wc; // No more commands in the pipeline
    exec_data_wc->next = NULL;

    return (exec_data_ls);
}

t_exec_data *test_8()
{
    ft_printf("Running test 8: ls > non_existent_dir/output.txt\n");
    t_exec_data *exec_data_ls = malloc(sizeof(t_exec_data));
    memset(exec_data_ls, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_ls);

    // Setup for ls command
    exec_data_ls->cmd = ft_strdup("/bin/ls"); // Command to execute
    exec_data_ls->opt = add_string_to_array("ls", exec_data_ls->opt);
    add_redir_to_list(&exec_data_ls->redirs, create_rdir(OUTPUT, build_full_path("non_existent_dir/output.txt")));
    
    exec_data_ls->next = NULL; // No more commands in the pipeline

    return (exec_data_ls);
}

t_exec_data *test_7()
{
    ft_printf("Running test 7: grep \"error\" test_input/log1.txt test_input/log2.txt | sort | tee test_output/errors_sorted.txt | wc -l > test_output/count.txt\n");
    t_exec_data *exec_data_grep = malloc(sizeof(t_exec_data));
    memset(exec_data_grep, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_grep);

    t_exec_data *exec_data_sort = malloc(sizeof(t_exec_data));
    memset(exec_data_sort, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_sort);

    t_exec_data *exec_data_tee = malloc(sizeof(t_exec_data));
    memset(exec_data_tee, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_tee);

    t_exec_data *exec_data_wc = malloc(sizeof(t_exec_data));
    memset(exec_data_wc, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_wc);

    // Setup for grep command
    exec_data_grep->cmd = ft_strdup("/bin/grep"); // Command to execute
    exec_data_grep->opt = add_string_to_array("grep", exec_data_grep->opt);
    exec_data_grep->opt = add_string_to_array("error", exec_data_grep->opt);
    exec_data_grep->opt = add_string_to_array(build_full_path("test_input/log1.txt"), exec_data_grep->opt);
    exec_data_grep->opt = add_string_to_array(build_full_path("test_input/log2.txt"), exec_data_grep->opt);

    // Setup for sort command
    exec_data_sort->cmd = ft_strdup("/usr/bin/sort"); // Command to execute
    exec_data_sort->opt = add_string_to_array("sort", exec_data_sort->opt);

    // Setup for tee command
    exec_data_tee->cmd = ft_strdup("/usr/bin/tee"); // Command to execute
    exec_data_tee->opt = add_string_to_array("tee", exec_data_tee->opt);
    exec_data_tee->opt = add_string_to_array(build_full_path("test_output/errors_sorted.txt"), exec_data_tee->opt);

    // Setup for wc command
    exec_data_wc->cmd = ft_strdup("/usr/bin/wc"); // Command to execute
    exec_data_wc->opt = add_string_to_array("wc", exec_data_wc->opt);
    exec_data_wc->opt = add_string_to_array("-l", exec_data_wc->opt);
    add_redir_to_list(&exec_data_wc->redirs, create_rdir(OUTPUT, build_full_path("test_output/count.txt")));

    // Link commands
    exec_data_grep->next = exec_data_sort;
    exec_data_sort->next = exec_data_tee;
    exec_data_tee->next = exec_data_wc;
    exec_data_wc->next = NULL;

    return (exec_data_grep);
}


t_exec_data *test_6()
{
    ft_printf("Running test 6: cat << EOF | grep \"hello\" > test_output/greetings.txt\n");
    t_exec_data *exec_data_cat = malloc(sizeof(t_exec_data));
    memset(exec_data_cat, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_cat);

    t_exec_data *exec_data_grep = malloc(sizeof(t_exec_data));
    memset(exec_data_grep, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_grep);

    // Setup for cat command with here-doc
    exec_data_cat->cmd = ft_strdup("/bin/cat"); // Command to execute
    exec_data_cat->opt = add_string_to_array("cat", exec_data_cat->opt);
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(HEREDOC_QUOTED, ft_strdup("EOF")));

    // Setup for grep command
    exec_data_grep->cmd = ft_strdup("/bin/grep"); // Command to execute
    exec_data_grep->opt = add_string_to_array("grep", exec_data_grep->opt);
    exec_data_grep->opt = add_string_to_array("hello", exec_data_grep->opt);
    add_redir_to_list(&exec_data_grep->redirs, create_rdir(OUTPUT, build_full_path("test_output/greetings.txt")));

    // Link commands
    exec_data_cat->next = exec_data_grep;
    exec_data_grep->next = NULL;

    return (exec_data_cat);
}


t_exec_data *test_5()
{
    ft_printf("Running test 5: cat test_input/input.txt test_input/input1.txt > test_output/combined.txt  \n");
    t_exec_data *exec_data_cat = malloc(sizeof(t_exec_data));
    memset(exec_data_cat, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_cat);

    // Setup for cat command
    exec_data_cat->cmd = ft_strdup("/bin/cat"); // Command to execute
    exec_data_cat->opt = add_string_to_array("cat", exec_data_cat->opt);
    exec_data_cat->opt = add_string_to_array(build_full_path("test_input/input.txt"), exec_data_cat->opt);
    exec_data_cat->opt = add_string_to_array(build_full_path("test_input/input1.txt"), exec_data_cat->opt);
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(OUTPUT, build_full_path("test_output/combined.txt")));

    exec_data_cat->next = NULL; // No more commands in the pipeline

    return (exec_data_cat);
}

t_exec_data *test_4()
{
    ft_printf("Running test 4: cat << EOF | wc -l\n");
    t_exec_data *exec_data_cat = malloc(sizeof(t_exec_data));
    memset(exec_data_cat, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_cat);

    t_exec_data *exec_data_wc = malloc(sizeof(t_exec_data));
    memset(exec_data_wc, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_wc);

    // Setup for cat command with here-doc
    exec_data_cat->cmd = ft_strdup("/bin/cat"); // Command to execute
    exec_data_cat->opt = add_string_to_array("cat", exec_data_cat->opt);
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(HEREDOC_QUOTED, ft_strdup("EOF")));

    // Setup for wc command
    exec_data_wc->cmd = ft_strdup("/bin/wc"); // Command to execute
    exec_data_wc->opt = add_string_to_array("wc", exec_data_wc->opt);
    exec_data_wc->opt = add_string_to_array("-l", exec_data_wc->opt);

    // Link commands
    exec_data_cat->next = exec_data_wc;
    exec_data_wc->next = NULL;

    return (exec_data_cat);
}


t_exec_data *test_3()
{
    ft_printf("Running test 3: ls | grep \"txt\" >> test_output/results.txt | sort\n");
    t_exec_data *exec_data_ls = malloc(sizeof(t_exec_data));
    memset(exec_data_ls, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_ls);

    t_exec_data *exec_data_grep = malloc(sizeof(t_exec_data));
    memset(exec_data_grep, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_grep);

    t_exec_data *exec_data_sort = malloc(sizeof(t_exec_data));
    memset(exec_data_sort, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_sort);

    // Setup for ls command
    exec_data_ls->cmd = ft_strdup("/bin/ls"); // Command to execute
    exec_data_ls->opt = add_string_to_array("ls", exec_data_ls->opt);

    // Setup for grep command
    exec_data_grep->cmd = ft_strdup("/bin/grep"); // Command to execute
    exec_data_grep->opt = add_string_to_array("grep", exec_data_grep->opt);
    exec_data_grep->opt = add_string_to_array("txt", exec_data_grep->opt);
    add_redir_to_list(&exec_data_grep->redirs, create_rdir(OUTPUT_APPEND, build_full_path("test_output/results.txt")));

    // Setup for sort command
    exec_data_sort->cmd = ft_strdup("/bin/sort"); // Command to execute
    exec_data_sort->opt = add_string_to_array("sort", exec_data_sort->opt);

    // Link commands
    exec_data_ls->next = exec_data_grep;
    exec_data_grep->next = exec_data_sort;
    exec_data_sort->next = NULL;

    return (exec_data_ls);
}


t_exec_data *test_2()
{
    ft_printf("Running test 2: echo Hello World > test_output/output.txt | wc -w < test_output/output.txt\n");
    t_exec_data *exec_data_echo = malloc(sizeof(t_exec_data));
    memset(exec_data_echo, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_echo);
    t_exec_data *exec_data_wc = malloc(sizeof(t_exec_data));
    memset(exec_data_wc, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_wc);

    // Setup for echo command
    exec_data_echo->cmd = ft_strdup("echo"); // Command to execute
    exec_data_echo->opt = add_string_to_array("echo", exec_data_echo->opt);
    exec_data_echo->opt = add_string_to_array("Hello", exec_data_echo->opt);
    exec_data_echo->opt = add_string_to_array("World", exec_data_echo->opt);
    exec_data_echo->is_builtin = true;
    add_redir_to_list(&exec_data_echo->redirs, create_rdir(OUTPUT, build_full_path("test_output/output.txt")));

    // Setup for wc command
    exec_data_wc->cmd = ft_strdup("/bin/wc"); // Command to execute
    exec_data_wc->opt = add_string_to_array("wc", exec_data_wc->opt);
    exec_data_wc->opt = add_string_to_array("-w", exec_data_wc->opt);
    add_redir_to_list(&exec_data_wc->redirs, create_rdir(INPUT, build_full_path("test_output/output.txt")));

    // Link commands
    exec_data_echo->next = exec_data_wc;
    exec_data_wc->next = NULL;

    return (exec_data_echo);
}

t_exec_data *test_1()
{
    ft_printf("Running test 1: cat < test_input/input1.txt > test_output/out1.txt > test_output/out2.txt | wc | sed 's/t/c/g'\n");
    t_exec_data *exec_data_cat = malloc(sizeof(t_exec_data));
    memset(exec_data_cat, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_cat);
    t_exec_data *exec_data_gr = malloc(sizeof(t_exec_data));
    memset(exec_data_gr, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_gr);
    t_exec_data *exec_data_sd = malloc(sizeof(t_exec_data));
    memset(exec_data_sd, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_sd);

    exec_data_cat->cmd = ft_strdup("/bin/cat"); // Command to execute
    exec_data_cat->opt = add_string_to_array("cat", exec_data_cat->opt);
   
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(INPUT, build_full_path("test_input/input1.txt")));
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(OUTPUT, build_full_path("test_output/out1.txt")));
    add_redir_to_list(&exec_data_cat->redirs, create_rdir(OUTPUT, build_full_path("test_output/out2.txt")));
    
    exec_data_gr->cmd = ft_strdup("/bin/wc"); // Command to execute
    exec_data_gr->opt = add_string_to_array("wc", exec_data_gr->opt);


    exec_data_sd->cmd = ft_strdup("/bin/sed"); // Command to execute
    exec_data_sd->opt = add_string_to_array("sed", exec_data_sd->opt);
    exec_data_sd->opt = add_string_to_array("s/t/c/g", exec_data_sd->opt);


    exec_data_cat->next = exec_data_gr;
    exec_data_gr->next = exec_data_sd;
    return (exec_data_cat);
}

t_exec_data *test_0()
{
    ft_printf("Running test 0: ls\n");
    t_exec_data *exec_data_one = malloc(sizeof(t_exec_data));
    memset(exec_data_one, 0, sizeof(t_exec_data)); // Initialize to 0
    init_cmd(exec_data_one);
    
    exec_data_one->cmd = ft_strdup("/bin/ls"); // Command to execute
    exec_data_one->opt = add_string_to_array("ls", exec_data_one->opt);
    exec_data_one->next = NULL;

    return (exec_data_one);
}

