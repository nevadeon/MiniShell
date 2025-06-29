#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef INCLUDE_TEST_HEADER
#  include "test.h"
# endif
# ifdef INCLUDE_TEST_MACRO
#  include "test_macro.h"
# endif

# define ARENA_BLOCK_SIZE 16384

# define GREEN "\001\033[1;32m\002"
# define PURPLE "\001\033[1;35m\002"
# define BROWN "\001\033[1;33m\002"
# define RESET "\001\033[0m\002"

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
# include "cbuiltins.h"
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
	E_NONE = 0,
	E_BAD_SUBSTITUTION,
	E_UNEXPECTED_TOKEN,
	E_UNCLOSED,
	E_PERM_DENIED,
	E_NO_FILE_OR_DIR,
	E_IS_DIR,
	E_CMD_NOT_FOUND,
	E_ALLOC_FAIL,
	E_NOT_EXECUTABLE,
	E_ACCESS,
	E_USE_ERRNO,
	E_UNHANDLED,
	E_UNKNOWN,
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
