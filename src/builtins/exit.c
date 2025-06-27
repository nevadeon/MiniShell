#include "cbuiltins.h"

static int	_print_error(t_ctx *ctx, const char *msg, const char *arg)
{
	if (arg)
		fprintf(stderr, "bash: exit: %s: %s\n", arg, msg);
	else
		fprintf(stderr, "bash: exit: %s\n", msg);
	ctx->last_exit_code = 1;
	return (1);
}

int	builtin_exit(t_ctx *ctx, char **args)
{
	int	status;
	int	i;

	printf("exit\n");
	if (args[1] && args[2])
		return (_print_error(ctx, "too many arguments", NULL));
	if (!args[1])
		exit(EXIT_SUCCESS);
	i = -1;
	while (args[1][++i])
	{
		if (!char_isnum(args[1][i]))
		{
			_print_error(ctx, "numeric argument required", args[1]);
			free_allocator(ctx->cmd);
			free_allocator(ctx->prog);
			exit(2);
		}
	}
	status = str_atoi(args[1]);
	free_allocator(ctx->cmd);
	free_allocator(ctx->prog);
	exit(status);
}
