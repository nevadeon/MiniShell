#include "minishell.h"
#include "tools/path.h"
#include "tools/env.h"
#include "builtins.h"

int	builtin_cd(__attribute__((unused)) t_alloc *alloc, __attribute__((unused)) t_str_list *args)
{
	exit(666);
	return (0);
}
