#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef INCLUDE_TEST_HEADER
#  include "test.h"
# endif
# ifdef INCLUDE_TEST_MACRO
#  include "test_macro.h"
# endif

# define ARENA_BLOCK_SIZE 4096

# include "forward.h"
# include "signals.h"
# include <assert.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# ifdef LINUX
#  include <linux/limits.h>
# endif
# include <limits.h>

# include "parsing.h"
# include "builtins.h"
# include "executing.h"

# include "tools/env.h"
# include "tools/char.h"
# include "tools/list.h"
# include "tools/num.h"
# include "tools/sort.h"
# include "tools/str.h"

# include "allocators/arena_allocator.h"
# include "allocators/block_allocator.h"
# include "allocators/malloc_allocator.h"
# include "allocators/mgc_allocator.h"

typedef struct s_str_list
{
	struct s_str_list	*next;
	char				*content;
}	t_str_list;

typedef enum e_shell_error
{
	ERR_NONE = 0,
	ERR_BAD_SUBSTITUTION,
	ERR_UNEXPECTED_TOKEN,
	ERR_UNCLOSED,
	ERR_PERM_DENIED,
	ERR_NO_FILE_OR_DIR,
	ERR_IS_DIR,
	ERR_CMD_NOT_FOUND,
}	t_shell_error;

typedef struct s_ctx
{
	t_alloc			**prog;
	t_alloc			**cmd;
	t_shell_error	last_error_type;
	int				last_exit_code;
	char			***env;
}	t_ctx;

char	*readline_prompt(t_alloc *alloc);
void	throw_error(t_ctx *ctx, t_shell_error err, char *arg);

#endif
