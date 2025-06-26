#include "minishell.h"

static const char	*_err_msg[] = {
	"",
	"bad substitution",
	"syntax error near expected token `",
	"unexpected EOF while looking for matching `",
	"Permission denied",
	"No such file or directory",
	"Is a directory",
	"command not found",
};

static const int	_err_code[] = {
	0,
	1,
	2,
	2,
	126,
	127,
	127,
	127
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
