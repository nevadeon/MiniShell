#include "minishell.h"

static const char	*g_err_msg[] = {
	"",
	"bad substitutions",
	"syntax error near expexted token `",
	"unexpected EOF while looking for matching `",
	"Permission denied",
	"No such file or directory",
	"Is a directory",
	"command not found",
};

static const int	g_err_code[] = {
	0,
	1,
	2,
	2,
	126,
	127,
	127,
	127
};

static const size_t			g_err_msg_size = \
	sizeof(g_err_msg) / sizeof(g_err_msg[0]);
static const size_t			g_err_code_size = \
	sizeof(g_err_code) / sizeof(g_err_code[0]);

void	throw_error(t_ctx *ctx, t_shell_error err, char *arg)
{
	assert(g_err_code_size == g_err_msg_size);
	if (err == ERR_UNEXPECTED_TOKEN || err == ERR_UNCLOSED)
		fprintf(stderr, "bash: %s%s'\n", g_err_msg[err], arg);
	else
		fprintf(stderr, "bash: %s: %s\n", arg, g_err_msg[err]);
	ctx->last_exit_code = g_err_code[err];
	ctx->last_error_type = err;
}
