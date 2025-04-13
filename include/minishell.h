#ifndef MINISHELL_H
# define MINISHELL_H

# include "mem.h"
# include "str.h"
# include "env.h"
# include "char.h"
# include "list.h"
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <dirent.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifdef INCLUDE_TEST_HEADER
#  include "test.h"
# endif

typedef struct	s_dir
{
	int		nb_dir;
	t_list	*head;
}	t_dir;

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
