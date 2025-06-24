#include "parsing.h"

void	remove_comment(t_alloc *alloc, char **input)
{
	size_t	index;
	size_t	comment_start;
	size_t	comment_end;

	index = 0;
	comment_start = 0;
	comment_end = 0;
	while ((*input)[index])
	{
		if ((*input)[index] == '#')
		{
			comment_start = index;
			while ((*input)[index] && (*input)[index] != '\n')
				index++;
			comment_end = index;
			index += str_replace(alloc, (t_replace){\
				.str = input, \
				.rep = "", \
				comment_start, \
				comment_end \
			});
		}
		index++;
	}
}
