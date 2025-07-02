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

bool	try_single_builtin(t_ctx *ctx, t_redir_list *redir_list, char **args)
{
	int	i;
	int	stdout_cpy;

	if (!args)
		return (false);
	i = -1;
	while (++i < (int)g_array_size)
	{
		if (str_cmp(g_builtin_name[i], args[CMD_NAME]) == 0)
		{
			stdout_cpy = NO_REDIR;
			if (!single_builtin_redirection(\
				ctx, redir_list, &stdout_cpy, args[CMD_NAME]))
				return (true);
			ctx->last_exit_code = g_builtin_fn[i](ctx, args);
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
