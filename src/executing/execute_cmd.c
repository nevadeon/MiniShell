#include "minishell.h"
#include "cbuiltins.h"

//Adding elements is safe, changing the order is not
static const char			*_builtin_name[] = {
	"cd",
	"exit",
	"export",
	"unset",
	"echo",
	"pwd",
	"env",
};

static const t_builtin_fn	_builtin_fn[] = {
	builtin_cd,
	builtin_exit,
	builtin_export,
	builtin_unset,
	builtin_echo,
	builtin_pwd,
	builtin_env,
};

static const size_t			g_array_size = \
sizeof(_builtin_name) / sizeof(_builtin_name[0]);

static void	_exec_failure_print(t_ctx *ctx, char **args)
{
	if (errno == EACCES)
		throw_error(ctx, ERR_PERM_DENIED, args[CMD_NAME]);
	else if (errno == ENOENT)
		throw_error(ctx, ERR_CMD_NOT_FOUND, args[CMD_NAME]);
	else
	{
		fprintf(stderr, "%s: %s\n", args[CMD_NAME], strerror(errno));
		ctx->last_exit_code = errno;
		ctx->last_error_type = ERR_UNKNOWN;
	}
}

bool	try_single_builtin(t_ctx *ctx, t_ast *ast)
{
	char	**args;
	int		i;

	args = (char **)lst_to_array(*ctx->cmd, (t_list *)ast->s_leaf.func);
	i = -1;
	while (++i < NO_FORK_MAX_INDEX)
	{
	if (str_cmp(_builtin_name[i], args[CMD_NAME]) == 0)
		{
			random_bash_redir(*ctx->cmd, ast->s_leaf.redir_in, ast->s_leaf.redir_out);
			_builtin_fn[i](ctx, args);
			return (true);
		}
	}
	return (false);
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
		while (++i < (int)g_array_size)
			if (str_cmp(_builtin_name[i], args[CMD_NAME]) == 0)
				exit(_builtin_fn[i](ctx, args));
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
