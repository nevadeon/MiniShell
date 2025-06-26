#include "cbuiltins.h"

int	builtin_exit(t_ctx *unused_ctx, char **args)
{
	int	status;
	int	i;

	(void)unused_ctx;
	if (args[1] && args[2])
		return (printf("bash: exit: too many arguments"), 1);
	if (!args[1])
		exit(EXIT_SUCCESS);
	i = -1;
	while (args[1][i])
	{
		if (!char_isnum(args[1][i]))
		{
			printf("bash: exit: %s: numeric argument required", args[1]);
			exit(2);
		}
	}
	status = str_atoi(args[1]);
	exit(status);
}
