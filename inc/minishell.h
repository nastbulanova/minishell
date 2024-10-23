#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "mini_signals.h"


typedef struct s_process
{
    pid_t pid;                      
    struct s_process* next;      
} t_process;

typedef struct s_shell_main
{
    t_process *process_head;                      
        
} t_shell_main;


extern t_shell_main global_shell;

void remove_process(pid_t pid);
void add_process(pid_t pid);
void print_process_list();

#endif