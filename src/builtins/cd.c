#include "minishell.h"
#include "tools/path.h"
#include "tools/env.h"
#include "cbuiltins.h"

static int	_print_error(t_ctx *ctx, const char *msg, const char *arg)
{
	if (arg)
		io_dprintf(STDERR, "bash: cd: %s: %s\n", arg, msg);
	else
		io_dprintf(STDERR, "bash: cd: %s\n", msg);
	ctx->last_exit_code = 1;
	return (1);
}

static char	*get_path_value(t_ctx *ctx, char **args)
{
	char	*oldpwd;
	char	*home;

	if (args[1] && args[2])
		return (_print_error(ctx, "too many arguments", NULL), NULL);
	if (args[1] && str_equals(args[1], "-"))
	{
		oldpwd = env_get_var_value(*ctx->env, "OLDPWD");
		if (!oldpwd)
			return (_print_error(ctx, "OLDPWD not set", NULL), NULL);
		return (oldpwd);
	}
	if (args[1])
		return (args[1]);
	home = env_get_var_value(*ctx->env, "HOME");
	if (!home)
		return (_print_error(ctx, "HOME not set", NULL), NULL);
	return (home);
}

int	builtin_cd(t_ctx *ctx, char **args)
{
	char	cwd[PATH_MAX];
	char	*path;

	path = get_path_value(ctx, args);
	if (!path)
		return (1);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	if (chdir(path))
		return (_print_error(ctx, "no such file or directory", path));
	env_set_var_value(ctx, str_vjoin(*ctx->prog, 2, "OLDPWD=", cwd));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	if (args[1] && str_equals(args[1], "-"))
		printf("%s\n", cwd);
	env_set_var_value(ctx, str_vjoin(*ctx->prog, 2, "PWD=", cwd));
	ctx->last_exit_code = 0;
	return (0);
}
