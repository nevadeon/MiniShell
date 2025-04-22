#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <unistd.h>
# include <linux/limits.h>
# include <limits.h>
# include <dirent.h>
# include "ast.h"
# include "char.h"
# include "env.h"
# include "executing.h"
# include "int.h"
# include "list.h"
# include "mem.h"
# include "num.h"
# include "sort.h"
# include "str.h"

# ifdef INCLUDE_TEST_HEADER
#  include "test.h"
# endif

typedef struct s_var
{
	size_t	start;
	size_t	name_start;
	size_t	end;
	size_t	name_end;
	bool	bracketed;
}	t_var;

void	handle_command(char *input);
bool	handle_escape(char *input, size_t *len, char c);
void	expand(char **word);
void	expand_tilde(char **word);
void	expand_wildcard(char **word);

#endif
