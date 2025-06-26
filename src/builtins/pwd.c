#include "cbuiltins.h"

int	builtin_pwd(t_ctx *ctx, char **unused_args)
{
	char	*pwd;

	(void)unused_args;
	pwd = env_get_var_value(*ctx->env, "PWD");
	if (!pwd)
		return (printf("bash: pwd: PWD not set\n"), 1);
	printf("%s\n", pwd);
	return (0);
}
