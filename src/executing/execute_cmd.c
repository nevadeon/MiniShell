#include "minishell.h"

//Adding elements is safe, changing the order is not
static const char			*g_builtin_name[] = {
	"cd",
	"exit",
	"export",
	"unset",
	"echo",
	"pwd",
	"env",
};

static const t_builtin_fn	g_builtin_fn[] = {
	builtin_cd,
	builtin_exit,
	builtin_export,
	builtin_unset,
	builtin_echo,
	builtin_pwd,
	builtin_env,
};

static const size_t			g_array_size = \
sizeof(g_builtin_name) / sizeof(g_builtin_name[0]);

bool	try_single_builtin(t_ctx *ctx, t_ast *a)
{
	char	**args;
	int		i;
	int		stdin_cpy;
	int		stdout_cpy;

	args = (char **)lst_to_array(*ctx->cmd, (t_list *)a->s_leaf.func);
	if (!args)
		return (false);
	i = -1;
	while (++i < (int)g_array_size)
	{
		if (str_cmp(g_builtin_name[i], args[CMD_NAME]) == 0)
		{
			stdin_cpy = builtin_redir_in(a->s_leaf.redir_in);
			stdout_cpy = builtin_redir_out(a->s_leaf.redir_out);
			g_builtin_fn[i](ctx, args);
			if (stdin_cpy)
				dup_close(stdin_cpy, STDIN_FILENO);
			if (stdout_cpy)
				dup_close(stdout_cpy, STDOUT_FILENO);
			return (true);
		}
	}
	return (false);
}

static bool	_try_builtin(t_ctx *ctx, char **args)
{
	int	i;

	i = -1;
	while (++i < (int)g_array_size)
		if (str_cmp(g_builtin_name[i], args[CMD_NAME]) == 0)
			return (g_builtin_fn[i](ctx, args), true);
	return (false);
}

static void	_try_relative_path(t_ctx *ctx, char **args)
{
	char	*path;

	path = str_vjoin(*ctx->cmd, 2, "./", args[CMD_NAME]);
	if (!path)
		return (throw_error(ctx, E_ALLOC_FAIL, args[CMD_NAME]));
	execve_on_path(ctx, path, args, E_NO_FILE_OR_DIR);
}

static void	_try_env_paths(t_ctx *ctx, char **env_paths, char **args)
{
	char	*path;

	while (*env_paths)
	{
		path = str_vjoin(*ctx->cmd, 3, *env_paths, "/", args[CMD_NAME]);
		if (!path)
			return (throw_error(ctx, E_ALLOC_FAIL, args[CMD_NAME]));
		execve_on_path(ctx, path, args, 0);
		env_paths++;
	}
	return (throw_error(ctx, E_CMD_NOT_FOUND, args[CMD_NAME]));
}

void	exec_cmd(t_ctx *ctx, char **env_paths, char **args)
{
	if (!args)
		return ;
	if (str_chr(args[CMD_NAME], '/'))
		return (execve_on_path(ctx, args[CMD_NAME], args, E_NO_FILE_OR_DIR));
	if (!env_paths)
		return (_try_relative_path(ctx, args));
	if (_try_builtin(ctx, args))
		return ;
	_try_env_paths(ctx, env_paths, args);
}
