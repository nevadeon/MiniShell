#include "parsing.h"

void	expand(t_alloc *alloc, char **input)
{
	expand_tilde(alloc, input);
	expand_variables(alloc, input);
	expand_wildcards(alloc, input);
}
