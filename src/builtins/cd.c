#include "minishell.h"
#include "path.h"
#include "env.h"
#include "builtins.h"

int	builtin_cd(__attribute__((unused)) t_alloc *alloc, __attribute__((unused)) t_str_list *args)
{
	exit(666);
	return (0);
}
