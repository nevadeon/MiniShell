#ifndef MINISHELL_H
# define MINISHELL_H

# include <assert.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# ifdef LINUX
#  include <linux/limits.h>
# endif
# include <limits.h>
# include "ast.h"
# include "char.h"
# include "env.h"
# include "parsing.h"
# include "builtins.h"
# include "int.h"
# include "list.h"
# include "num.h"
# include "sort.h"
# include "str.h"
# include "allocator.h"
# include "dynamic_arena.h"
# include "fixed_arena.h"

# ifdef INCLUDE_TEST_HEADER
#  include "test.h"
# endif

# define ARENA_BLOCK_SIZE 4096

typedef struct s_var
{
	size_t	start;
	size_t	name_start;
	size_t	end;
	size_t	name_end;
	bool	bracketed;
}	t_var;

void	handle_command(t_allocator *alloc, char *input);
bool	handle_escape(char *input, size_t *len, char c);
void	expand(t_allocator *alloc, char **word, char **input);
void	expand_tilde(t_allocator *alloc, char **word);
void	expand_wildcard(t_allocator *alloc, char **input, char **word);
char	*readline_prompt(char *buf, size_t size);

#endif
