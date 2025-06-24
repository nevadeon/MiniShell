#include "parsing.h"

static const char	*g_errors_messages[] = {
	"",
	"bad substitution",
	"syntax error near unexpected token `"
};

void	toggle_pars_err(t_parsing_errors err_code, char *arg)
{
	if (err_code == E_PARS_UNEX_TOKEN)
		fprintf(stderr, "bash: %s%s'\n", g_errors_messages[err_code], arg);
	else
		fprintf(stderr, "bash: %s: %s\n", arg, g_errors_messages[err_code]);
	errno = err_code;
}
