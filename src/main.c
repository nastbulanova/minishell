/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaomigu <joaomigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:39:30 by joaomigu          #+#    #+#             */
/*   Updated: 2025/03/02 16:03:12 by joaomigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @file main.c
 * @brief Entry point and main loop for the Minishell project.
 */

/**
 * @brief Exits the minishell program, freeing allocated resources.
 *
 * @param msg Optional exit message (can be NULL).
 * @param exit_code Exit status code.
 * @param exit_fd File descriptor for printing the exit message.
 * @param dispose_msg Whether to free the message string after use.
 */
void	minishell_exit(char *msg, int exit_code, int exit_fd, bool dispose_msg)
{
	t_minishell	*data;

	data = get_shell(false);
	if (msg)
	{
		ft_putstr_fd(msg, exit_fd);
		if (dispose_msg)
			free(msg);
	}
	minishell_free(data);
	if (exit_code < 0)
		exit_code = data->exit_code;
	exit((unsigned char)exit_code);
}

/**
 * @brief Displays the splash screen with ASCII art and a welcome message.
 */
void	display_splash_screen(void)
{
	printf("\033[H\033[J");
	printf("==========================================\
===========================\n");
	printf("                    Welcome to akitsenk &\
 joaomigu's\n");
	printf("=======================================\
==============================\n");
	printf(RB "MM    MM IIIII NN   NN IIIII  SSSSS  HH\
   HH  EEEEEEE LL      LL      \n");
	printf("MMM  MMM  III  NNN  NN  III  SS      HH   HH\
  EE      LL      LL      \n");
	printf("MM MM MM  III  NN N NN  III   SSSSS  HHHHHHH\
  EEEEE   LL      LL      \n");
	printf("MM    MM  III  NN  NNN  III       SS HH   HH\
  EE      LL      LL      \n");
	printf("MM    MM IIIII NN   NN IIIII  SSSSS  HH   HH\
  EEEEEEE LLLLLLL LLLLLLL \n" RST);
	printf("=============================================\
========================\n");
	printf("\n");
}

/**
 * @brief Processes user input by tokenizing, parsing, and executing commands.
 *
 * @param data Pointer to the minishell instance.
 * @param input The user input string to process.
 */
static void	process_input(t_minishell *data, char *input)
{
	t_parser_error	lexer_result;

	lexer_result = lexer(data, input);
	if (lexer_result == OK)
	{
		if (parser(data) == OK)
		{
			data->exit_code = 0;
			if (data->list_exec_data && data->list_exec_data->cmd)
				execute_command_list(data, data->list_exec_data);
			free_parser_data(&data);
		}
	}
}

/**
 * @brief The main execution loop of the shell.
 *
 * @param data Pointer to the minishell instance.
 */
static void	main_loop(t_minishell *data)
{
	char	*input;

	set_state_signal_handlers(MAIN);
	while (TRUE)
	{
		update_prompt(data);
		input = readline(data->prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input[0])
		{
			add_history(input);
			if (!is_string_empty(input))
				process_input(data, input);
		}
		free(input);
	}
	if (data)
		minishell_free(data);
}

/**
 * @brief Entry point of the minishell program.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param envp Environment variables.
 * @return int Exit status.
 */
int	main(int argc, char **argv, char **envp)
{
	t_minishell	*data;

	(void)argv;
	data = get_shell(true);
	if (argc != 1)
		error_exit(RB "Minishell takes no arguments. Exiting." RST,
			"main in main.c");
	if (!*envp)
	{
		ft_putendl_fd(RB "No environment variables found." RST, STDOUT_FILENO);
		ft_putendl_fd(GB "Initializing defaults." RST, STDOUT_FILENO);
		env_init_default(argv, data);
	}
	env_init(argv, envp, data);
	display_splash_screen();
	main_loop(data);
	return (0);
}
