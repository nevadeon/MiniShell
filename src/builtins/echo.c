#include "minishell.h"
#include "cbuiltins.h"

int	builtin_echo(t_ctx *unused_ctx, char **args)
{
	bool	newline;
	int		i;

	(void)unused_ctx;
	if (!args[1])
		return (printf("\n"), 0);
	newline = (str_cmp(args[1], "-n") != 0);
	i = !newline + 1;
	printf("%s", args[i]);
	while (args[++i])
		printf(" %s", args[i]);
	if (newline)
		printf("\n");
	return (0);
}
