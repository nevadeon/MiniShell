#include "cbuiltins.h"
#include "allocators/allocator.h"

static int	_print_error(t_ctx *ctx, const char *msg)
{
	fprintf(stderr, "bash: env: %s\n", msg);
	ctx->last_exit_code = 1;
	return (1);
}

int	builtin_env(t_ctx *ctx, char **unused_args)
{
	char	**env;
	int		i;

	if (unused_args[1])
		return (_print_error(ctx, "too many arguments"));
	(void)unused_args;
	env = *ctx->env;
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return (0);
}
