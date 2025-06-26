#include "minishell.h"
#include "tools/path.h"
#include "tools/env.h"
#include "cbuiltins.h"

// static const char	*g_cd_error_msg[] = {
// 	E_ERR_CD_OK = "No error",
// 	E_ERR_CD_ARGS = "too many arguments",
// 	E_ERR_CD_FILE_EXIST = "No such file or directory",
// 	E_ERR_CD_NOT_DIR = "Not a directory"
// }

// static void	_print_err(t_error_cd e, char *path)
// {
// 	printf("[cd] %s", g_cd_error_msg[e]);
// 	if (path)
// 		printf(": %s", path);
// 	printf("\n");
// }

void print_error(const char *first, ...) {
	va_list	args;
	char	*str;

	va_start(args, first);
	printf("bash: %s", first);
	while (1)
	{
		str = va_arg(args, char *);
		if (!str)
			break ;
		printf(": %s", str);
	}
	printf("\n");
	va_end(args);
}

int	builtin_cd(t_ctx *ctx, char **args)
{
	char	cwd[PATH_MAX];
	char	*path;

	if (args[1] && args[2])
		return (print_error("cd: too many arguments", NULL), 1);
	if (args[1])
	{
		path = args[1];
		if (str_equals(path, "-"))
			path = env_get_var_value(*ctx->env, "OLDPWD");
	}
	else
	{
		path = env_get_var_value(*ctx->env, "HOME");
		if (!path)
			return (print_error("cd: HOME not set", NULL), 1);
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	if (chdir(path))
		return (print_error("cd", path, strerror(errno), NULL), 1);
	env_set_var_value(ctx, str_vjoin(*ctx->prog, 2, "OLDPWD=", cwd));
	return (0);
}
