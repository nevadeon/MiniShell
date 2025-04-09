#ifndef MINISHELL_H
# define MINISHELL_H

# include "umgc.h"
# include "str.h"
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

void	handle_command(char *input);
void	handle_escape(char *input, ssize_t *len, bool *escape, char c);

#endif