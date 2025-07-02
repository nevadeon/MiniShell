#include "minishell.h"

static const char	*g_err_msg[] = {
[E_NONE] = "",
[E_BAD_SUBSTITUTION] = "bad substitution",
[E_UNEXPECTED_TOKEN] = "syntax error near unexpected token `",
[E_UNCLOSED] = "unexpected EOF while looking for matching `",
[E_UNHANDLED] = "not handled char `",
[E_PERM_DENIED] = "Permission denied",
[E_NO_FILE_OR_DIR] = "No such file or directory",
[E_IS_DIR] = "Is a directory",
[E_CMD_NOT_FOUND] = "command not found",
[E_NOT_EXECUTABLE] = "cannot execute binary file: Exec format error",
[E_ALLOC_FAIL] = "allocation failed",
[E_HDOC_QUIT] = "warning: here-document delimited by end-of-file (wanted `",
[E_HDOC_INT] = "",
[E_USE_ERRNO] = "",
[E_UNKNOWN] = "",
};

static const int	g_err_code[] = {
[E_NONE] = 0,
[E_BAD_SUBSTITUTION] = 1,
[E_UNEXPECTED_TOKEN] = 2,
[E_UNCLOSED] = 2,
[E_UNHANDLED] = 2,
[E_PERM_DENIED] = 126,
[E_NO_FILE_OR_DIR] = 127,
[E_IS_DIR] = 126,
[E_CMD_NOT_FOUND] = 127,
[E_NOT_EXECUTABLE] = 126,
[E_ALLOC_FAIL] = 1,
[E_HDOC_QUIT] = 0,
[E_HDOC_INT] = 130,
[E_USE_ERRNO] = 1,
[E_UNKNOWN] = 1,
};

static const size_t	g_err_msg_size = \
	sizeof(g_err_msg) / sizeof(g_err_msg[0]);
static const size_t	g_err_code_size = \
	sizeof(g_err_code) / sizeof(g_err_code[0]);

void	throw_error(t_ctx *ctx, t_shell_error err, char *arg)
{
	assert(g_err_code_size == g_err_msg_size);
	ctx->last_exit_code = g_err_code[err];
	if (g_err_code[err] != 0)
		ctx->last_error_type = err;
	if (err == E_HDOC_INT)
		return ;
	else if (err == E_CMD_NOT_FOUND)
		io_dprintf(STDERR, "bash: %s: %s\n", arg, g_err_msg[err]);
	else if (err == E_USE_ERRNO)
	{
		ctx->last_exit_code = errno;
		io_dprintf(STDERR, "bash: %s: %s\n", arg, strerror(errno));
	}
	else if (err == E_UNEXPECTED_TOKEN || err == E_UNCLOSED
		|| err == E_UNHANDLED)
		io_dprintf(STDERR, "bash: %s%s'\n", g_err_msg[err], arg);
	else
		io_dprintf(STDERR, "bash: %s: %s\n", arg, g_err_msg[err]);
}
