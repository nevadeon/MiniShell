#include "minishell.h"

bool	handle_escape(char *input, size_t *len, char c)
{
	bool	escape;

	escape = false;
	while (input[(*len)] && (input[(*len)] == c || escape))
	{
		if (input[(*len)] == '"')
			escape = !escape;
		(*len)++;
	}
	if (escape)
	{
		fprintf(stderr, "quote error\n");
		exit(EXIT_FAILURE);
	}
	return (true);
}
