#include "minishell.h"

static const char	*_err_msg[] = {
	[ERR_NONE] = "",
	[ERR_BAD_SUBSTITUTION] = "bad substitution",
	[ERR_UNEXPECTED_TOKEN] = "syntax error near expected token `",
	[ERR_UNCLOSED] = "unexpected EOF while looking for matching `",
	[ERR_PERM_DENIED] = "Permission denied",
	[ERR_NO_FILE_OR_DIR] = "No such file or directory",
	[ERR_IS_DIR] = "Is a directory",
	[ERR_CMD_NOT_FOUND] = "command not found",
};

static const int	_err_code[] = {
	[ERR_NONE] = 0,
	[ERR_BAD_SUBSTITUTION] = 1,
	[ERR_UNEXPECTED_TOKEN] = 2,
	[ERR_UNCLOSED] = 2,
	[ERR_PERM_DENIED] = 126,
	[ERR_NO_FILE_OR_DIR] = 127,
	[ERR_IS_DIR] = 127,
	[ERR_CMD_NOT_FOUND] = 127
};

static const size_t	_err_msg_size = \
	sizeof(_err_msg) / sizeof(_err_msg[0]);
static const size_t	_err_code_size = \
	sizeof(_err_code) / sizeof(_err_code[0]);

void	throw_error(t_ctx *ctx, t_shell_error err, char *arg)
{
	assert(_err_code_size == _err_msg_size);
	if (err == ERR_UNEXPECTED_TOKEN || err == ERR_UNCLOSED)
		fprintf(stderr, "bash: %s%s'\n", _err_msg[err], arg);
	else
		fprintf(stderr, "bash: %s: %s\n", arg, _err_msg[err]);
	ctx->last_exit_code = _err_code[err];
	ctx->last_error_type = err;
}
