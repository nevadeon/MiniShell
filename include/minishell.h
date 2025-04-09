#ifndef MINISHELL_H
# define MINISHELL_H

# include "umgc.h"
# include "str.h"
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

void	handle_command(char *input);
bool	handle_escape(char *input, size_t *len, char c);

#endif