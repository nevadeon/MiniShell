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
# include "list.h"
# include "num.h"
# include "sort.h"
# include "str.h"
# include "allocator.h"
# include "arena_allocator.h"
# include "block_allocator.h"
# include "malloc_allocator.h"
# include "mgc_allocator.h"
# include "executing.h"

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

void	handle_command(t_alloc **alloc_prog, t_alloc **alloc_cmd, char *input);
bool	handle_escape(char *input, size_t *len, char c);
void	expand(t_alloc *alloc, char **word, char **input);
void	expand_tilde(t_alloc *alloc, char **word);
void	expand_wildcard(t_alloc *alloc, char **input, char **word);
char	*readline_prompt(t_alloc *alloc);
void	input_loop(t_alloc *alloc_prog);

#endif
