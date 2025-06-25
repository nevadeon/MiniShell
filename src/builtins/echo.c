#include "minishell.h"
#include "builtins.h"

int	builtin_echo(t_ctx *unused_ctx, char **args)
{
	bool	insert_newline;
	int		i;

	(void)unused_ctx;
	if (!args[1])
		return (printf("\n"), 0);
	insert_newline = (str_cmp(args[1], "-n") != 0);
	i = !insert_newline + 1;
	printf("%s", args[i]);
	while (args[++i])
		printf(" %s", args[i]);
	if (insert_newline)
		printf("\n");
	return (0);
}
