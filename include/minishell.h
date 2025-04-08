#ifndef MINISHELL_H
# define MINISHELL_H

# include "mgc.h"
# include "str.h"
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

void	handle_command(char *input);

#endif