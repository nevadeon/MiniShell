#include "parsing.h"

void	expand_tilde(t_alloc *alloc, char **input)
{
	size_t	index;

	index = 0;
	while ((*input)[index])
	{
		str_escape((*input), &index, '\'', '\'');
		str_escape((*input), &index, '"', '"');
		if ((*input)[index] == '~')
		{
			index += str_replace(alloc, (t_replace){\
				.str = input,
				.rep = "${HOME}",
				.start = index,
				.end = index + 1
			});
		}
		else
			index++;
	}
}
