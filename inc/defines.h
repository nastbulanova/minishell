#ifndef DEFINES_H
# define DEFINES_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <stdbool.h>
# include <errno.h>
# include "../libs/libft/include/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_env t_env;
typedef struct s_minishell t_minishell;
typedef struct	s_exec_data t_exec_data;
typedef struct	s_token t_token;
typedef struct s_shell_info t_shell_info;

//default color
# define RST "\033[0m" 
//RED Color (Bold)
# define RN   "\033[0;31m" 
# define RB   "\033[1;31m" 
//GREEN Color (Bold)
# define GN   "\033[0;32m"
# define GB   "\033[1;32m"
//YELLOW Color (Bold)
# define YN   "\033[0;33m" 
# define YB   "\033[1;33m" 
//BLUE Color (Bold)
# define BN   "\033[0;34m" 
# define BB   "\033[1;34m" 
//MAGENTA Color (Bold)
# define MN   "\033[0;35m"
# define MB   "\033[1;35m"
//CYAN Color (Bold)
# define CN   "\033[0;36m"
# define CB   "\033[1;36m"
//WHITE Color (Bold)
# define WN   "\033[0;37m"
# define WB   "\033[1;37m"

typedef enum e_signal_state
{
    MAIN,
    CHILD,
    HERE_DOC
} t_signal_state;

#endif
