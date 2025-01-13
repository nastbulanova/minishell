#ifndef DEFINES_H
# define DEFINES_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
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
# define RST "\001\033[0m\002" 
//RED Color (Bold)
# define RN   "\001\033[0;31m\002" 
# define RB   "\001\033[1;31m\002" 
//GREEN Color (Bold)
# define GN   "\001\033[0;32m\002"
# define GB   "\001\033[1;32m\002"
//YELLOW Color (Bold)
# define YN   "\001\033[0;33m\002" 
# define YB   "\001\033[1;33m\002" 
//BLUE Color (Bold)
# define BN   "\001\033[0;34m\002" 
# define BB   "\001\033[1;34m\002" 
//MAGENTA Color (Bold)
# define MN   "\001\033[0;35m\002"
# define MB   "\001\033[1;35m\002"
//CYAN Color (Bold)
# define CN   "\001\033[0;36m\002"
# define CB   "\001\033[1;36m\002"
//WHITE Color (Bold)
# define WN   "\001\033[0;37m\002"
# define WB   "\001\033[1;37m\002"

typedef enum e_signal_state
{
    MAIN,
    CHILD,
    HERE_DOC
} t_signal_state;

typedef enum s_redir_type
{
    OUTPUT, 
    OUTPUT_APPEND,
    INPUT, 
    HEREDOC,
    HEREDOC_QUOTED

}   t_redir_type;

#endif
