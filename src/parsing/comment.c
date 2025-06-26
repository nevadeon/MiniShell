#include "parsing.h"

void	remove_comment(t_alloc *alloc, char **input)
{
	size_t	index;
	size_t	comment_start;
	size_t	comment_end;

	index = 0;
	while ((*input)[index])
	{
		if ((*input)[index] == '#')
		{
			comment_start = index;
			while ((*input)[index] && (*input)[index] != '\n')
				index++;
			comment_end = index;
			str_replace(alloc, (t_replace){
				.str = input,
				.rep = "",
				.start = comment_start,
				.end = comment_end
			});
			index = comment_start;
			continue ;
		}
		index++;
	}
}
