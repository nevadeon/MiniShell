#include "minishell.h"

static void	_exec_failure_print(t_ctx *ctx, char **args)
{
	if (errno == EACCES)
		throw_error(ctx, ERR_PERM_DENIED, args[CMD_NAME]);
	else if (errno == ENOENT)
		throw_error(ctx, ERR_CMD_NOT_FOUND, args[CMD_NAME]);
	else
		fprintf(stderr, "%s: %s\n", args[CMD_NAME], strerror(errno));
}

void	exec_cmd(t_ctx *ctx, char **env_paths, char **args)
{
	char	*path;
	int		i;

	if (str_chr(args[CMD_NAME], '/'))
		execve(args[CMD_NAME], args, *ctx->env);
	else
	{
		i = -1;
		while (env_paths[++i])
		{
			path = str_vjoin(*ctx->cmd, 3, env_paths[i], "/", args[CMD_NAME]);
			execve(path, args, *ctx->env);
			if (errno != ENOENT)
				break ;
		}
	}
	_exec_failure_print(ctx, args);
}
