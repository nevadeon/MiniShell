#include "executing.h"

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

static int	_replace_fd(int src, int dest)
{
	int	dest_temp;

	if (src < 0 || dest < 0)
		return (-1);
	dest_temp = dup(dest);
	dup2(src, dest);
	return (dest_temp);
}

bool	try_single_builtin(t_ctx *ctx, int redir_fd[2], char **args)
{
	int	i;
	int	stdin_cpy;
	int	stdout_cpy;

	if (!args)
		return (false);
	i = -1;
	while (++i < (int)g_array_size)
	{
		if (str_cmp(g_builtin_name[i], args[CMD_NAME]) == 0)
		{
			stdin_cpy = _replace_fd(redir_fd[IN], STDIN_FILENO);
			stdout_cpy = _replace_fd(redir_fd[OUT], STDOUT_FILENO);
			ctx->last_exit_code = g_builtin_fn[i](ctx, args);
			dup2_close(stdin_cpy, STDIN_FILENO);
			dup2_close(stdout_cpy, STDOUT_FILENO);
			return (true);
		}
	}
	return (false);
}

bool	try_builtin(t_ctx *ctx, char **args)
{
	int	i;

	i = -1;
	while (++i < (int)g_array_size)
		if (str_cmp(g_builtin_name[i], args[CMD_NAME]) == 0)
			return (g_builtin_fn[i](ctx, args), true);
	return (false);
}
