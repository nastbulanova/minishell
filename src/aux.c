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

void *safe_malloc(size_t bytes, const char *function_name)
{
    void *ret;
 
    ret = malloc(bytes);
    if (!ret)
        error_exit("Error on memory allocation", function_name);
    ft_memset(ret, 0,bytes);
    return (ret);
}

void error_exit(const char *error, const char *function_name)
{
    t_minishell *data;

    data = get_shell(NULL);
    env_free(data->env);
    free(data);
    ft_printf(RB "%s (%s)\n" RST, error, function_name);//todo change to stderr
    exit(EXIT_FAILURE);
}
void minishell_free(t_minishell *shell)
{
    if (shell->env)
        env_free(shell->env);
    free(shell);
}