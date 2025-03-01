/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akitsenk <akitsenk@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:35:15 by joaomigu          #+#    #+#             */
/*   Updated: 2025/02/28 21:57:42 by akitsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "../libs/libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>

# define CONST_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:\
/usr/bin:/sbin:/bin:/snap/bin"
# define CONST_BUILTIN "echo cd pwd export unset env exit"

// default color
# define RST "\001\033[0m\002"
// RED Color (Bold)
# define RN "\001\033[0;31m\002"
# define RB "\001\033[1;31m\002"
// GREEN Color (Bold)
# define GN "\001\033[0;32m\002"
# define GB "\001\033[1;32m\002"
// YELLOW Color (Bold)
# define YN "\001\033[0;33m\002"
# define YB "\001\033[1;33m\002"
// BLUE Color (Bold)
# define BN "\001\033[0;34m\002"
# define BB "\001\033[1;34m\002"
// MAGENTA Color (Bold)
# define MN "\001\033[0;35m\002"
# define MB "\001\033[1;35m\002"
// CYAN Color (Bold)
# define CN "\001\033[0;36m\002"
# define CB "\001\033[1;36m\002"
// WHITE Color (Bold)
# define WN "\001\033[0;37m\002"
# define WB "\001\033[1;37m\002"

typedef enum e_signal_state
{
	MAIN,
	CHILD,
	HERE_DOC,
	IGNORE
}	t_signal_state;

typedef enum s_redir_type
{
	OUTPUT,
	OUTPUT_APPEND,
	INPUT,
	HEREDOC,
	HEREDOC_QUOTED,
	AMBIGUOUS
}	t_redir_type;

typedef enum s_parser_error
{
	OK,
	MALLOC_ERROR,
	SYNTAX_ERROR,
	PIPE_ERROR,
	FORK_ERROR,
	CLOSE_FD_ERROR,
	CTRLC
}	t_parser_error;

typedef enum s_token_type
{
	WORD,
	ENV_VAR,
	FIELD,
	REDIR_OUT,
	REDIR_IN,
	REDIR_APPEND,
	REDIR_HEREDOC,
	PIPE,
	NOT_EXIST
}	t_token_type;

#endif
