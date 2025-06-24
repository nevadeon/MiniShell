#include "str.h"

bool	str_escape(char *s, size_t *index, char start, char end)
{
	assert(s);
	if (!s[*index])
		return (true);
	if (s[*index] != start)
		return (true);
	(*index)++;
	while (s[*index] && s[*index] != end)
		(*index)++;
	if (s[*index] == end)
	{
		(*index)++;
		return (true);
	}
	return (false);
}
