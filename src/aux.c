#include  "../inc/minishell.h"

void display_splash_screen(void)
{
    // Clear the screen using ANSI escape codes
    printf("\033[H\033[J");

    // ASCII art for the splash screen
    
    printf("=====================================================================\n");
    printf("                    Welcome to akitsenk & joaomigu's\n");
    printf("=====================================================================\n");
    printf(RB "MM    MM IIIII NN   NN IIIII  SSSSS  HH   HH EEEEEEE LL      LL      \n");
    printf("MMM  MMM  III  NNN  NN  III  SS      HH   HH EE      LL      LL      \n");
    printf("MM MM MM  III  NN N NN  III   SSSSS  HHHHHHH EEEEE   LL      LL      \n");
    printf("MM    MM  III  NN  NNN  III       SS HH   HH EE      LL      LL      \n");
    printf("MM    MM IIIII NN   NN IIIII  SSSSS  HH   HH EEEEEEE LLLLLLL LLLLLLL \n" RST);
    printf("=====================================================================\n");
    printf("\n");
}

void *safe_malloc(size_t bytes)
{
    void *ret;
 
    ret = malloc(bytes);
    if (!ret)
        minishell_exit("Error on memory allocation", 1, STDERR_FILENO);  
    ft_memset(ret, 0,bytes);
    return (ret);
}

void error_exit(const char *error, const char *function_name)
{
    t_minishell *data;

    data = get_shell(NULL);
    ft_putstr_fd(RB "", STDERR_FILENO);
    ft_putstr_fd((char *)error, STDERR_FILENO);
    ft_putstr_fd(" ", STDERR_FILENO);
    ft_putstr_fd((char *)function_name, STDERR_FILENO);
    ft_putstr_fd("\n" RST, STDERR_FILENO);
    minishell_free(data);
    exit(EXIT_FAILURE);
}
void minishell_free(t_minishell *data)
{
    if (data)
    {  
        if (data->prompt)
            free(data->prompt);
        if (data->env)
            env_free(data->env);
        //free(data);
    }
    clear_history();
}