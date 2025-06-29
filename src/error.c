#include "minishell.h"

static const char	*_err_msg[] = {
	[E_NONE] = "",
	[E_BAD_SUBSTITUTION] = "bad substitution",
	[E_UNEXPECTED_TOKEN] = "syntax error near expected token `",
	[E_UNCLOSED] = "unexpected EOF while looking for matching `",
	[E_PERM_DENIED] = "Permission denied",
	[E_NO_FILE_OR_DIR] = "No such file or directory",
	[E_IS_DIR] = "Is a directory",
	[E_CMD_NOT_FOUND] = "command not found",
	[E_NOT_EXECUTABLE] = "cannot execute binary file: Exec format error",
	[E_ALLOC_FAIL] = "allocation failed",
	[E_USE_ERRNO] = "",
	[E_UNKNOWN] = "",
};

static const int	_err_code[] = {
	[E_NONE] = 0,
	[E_BAD_SUBSTITUTION] = 1,
	[E_UNEXPECTED_TOKEN] = 2,
	[E_UNCLOSED] = 2,
	[E_PERM_DENIED] = 126,
	[E_NO_FILE_OR_DIR] = 127,
	[E_IS_DIR] = 127,
	[E_CMD_NOT_FOUND] = 127,
	[E_NOT_EXECUTABLE] = 126,
	[E_ALLOC_FAIL] = 1,
	[E_USE_ERRNO] = 1,
	[E_UNKNOWN] = 1,
};

static const size_t	_err_msg_size = \
	sizeof(_err_msg) / sizeof(_err_msg[0]);
static const size_t	_err_code_size = \
	sizeof(_err_code) / sizeof(_err_code[0]);

void	throw_error(t_ctx *ctx, t_shell_error err, char *arg)
{
	assert(_err_code_size == _err_msg_size);
	ctx->last_exit_code = _err_code[err];
	ctx->last_error_type = err;
	if (err == E_USE_ERRNO)
	{
		ctx->last_exit_code = errno;
		io_dprintf(STDERR, "bash: %s: %s\n", arg, strerror(errno));
	}
	else if (err == E_UNEXPECTED_TOKEN || err == E_UNCLOSED)
		io_dprintf(STDERR, "bash: %s%s'\n", _err_msg[err], arg);
	else
		io_dprintf(STDERR, "bash: %s: %s\n", arg, _err_msg[err]);
}
