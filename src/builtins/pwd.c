#include "cbuiltins.h"

int	builtin_pwd(t_ctx *unused_ctx, char **unused_args)
{
	char	cwd[PATH_MAX];

	(void)unused_ctx;
	(void)unused_args;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	printf("%s\n", cwd);
	return (0);
}
