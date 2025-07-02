#include "executing.h"

static void	_execve_on_path(t_ctx *ctx, char *path, char **args, int error_code)
{
	struct stat	sb;

	if (stat(path, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
			return (throw_error(ctx, E_IS_DIR, args[CMD_NAME]));
		execve(path, args, *ctx->env);
		if (errno == EACCES)
			return (throw_error(ctx, E_PERM_DENIED, args[CMD_NAME]));
		if (errno == ENOEXEC)
			return (throw_error(ctx, E_NOT_EXECUTABLE, args[CMD_NAME]));
		if (errno != ENOENT)
			return (throw_error(ctx, E_USE_ERRNO, args[CMD_NAME]));
	}
	if (error_code)
		throw_error(ctx, error_code, args[CMD_NAME]);
}

static void	_try_absolute_path(t_ctx *ctx, char **args)
{
	_execve_on_path(ctx, args[CMD_NAME], args, E_NO_FILE_OR_DIR);
}

static void	_try_relative_path(t_ctx *ctx, char **args)
{
	char	*path;

	path = str_vjoin(*ctx->cmd, 2, "./", args[CMD_NAME]);
	if (!path)
		return (throw_error(ctx, E_ALLOC_FAIL, args[CMD_NAME]));
	_execve_on_path(ctx, path, args, E_NO_FILE_OR_DIR);
}

static void	_try_env_paths(t_ctx *ctx, char **env_paths, char **args)
{
	char	*path;

	while (*env_paths)
	{
		path = str_vjoin(*ctx->cmd, 3, *env_paths, "/", args[CMD_NAME]);
		if (!path)
			return (throw_error(ctx, E_ALLOC_FAIL, args[CMD_NAME]));
		_execve_on_path(ctx, path, args, 0);
		env_paths++;
	}
	return (throw_error(ctx, E_CMD_NOT_FOUND, args[CMD_NAME]));
}

void	execute_command(t_ctx *ctx, char **env_paths, char **args)
{
	if (!args)
		return ;
	if (str_chr(args[CMD_NAME], '/'))
		return (_try_absolute_path(ctx, args));
	if (!env_paths)
		return (_try_relative_path(ctx, args));
	if (try_builtin(ctx, args))
		return ;
	_try_env_paths(ctx, env_paths, args);
}
