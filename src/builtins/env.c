#include "cbuiltins.h"
#include "allocators/allocator.h"

int	builtin_env(t_ctx *ctx, char **unused_args)
{
	char	**env;
	int		i;

	(void)unused_args;
	env = *ctx->env;
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return (0);
}
