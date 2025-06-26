#include "cbuiltins.h"

int	builtin_unset(t_ctx *ctx, char **args)
{
	while (*args)
	{
		env_remove_var(ctx, *args);
		args++;
	}
	return (0);
}
