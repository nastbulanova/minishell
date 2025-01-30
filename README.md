# minishell

Files only for test: for_test.c env_to_ll.c
If you will remove for_test.c this will cause leaks - the lexer and parser only free the memory allocated inside these functions. for_test contains declarations and frees.

If you need to use the open_field function for heredoc, you don't need to tokenize the string, just cast it to the t_token type, where token->start = string. open_field will return char*.
