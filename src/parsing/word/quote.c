#include "minishell.h"

void	handle_escape(char *input, ssize_t *len, bool *escape, char c)
{
	while (input[(*len)] && (input[(*len)] == c || *escape))
	{
		if (input[(*len)] == '"')
			*escape = !*escape;
		(*len)++;
	}
}
