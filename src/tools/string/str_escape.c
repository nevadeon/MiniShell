#include "tools/str.h"

bool	str_escape(char *s, size_t *index, char start, char end)
{
	assert(s);
	assert(index);

	if (!s[*index] || s[*index] != start)
		return (true);
	(*index)++;
	while (s[*index] && s[*index] != end)
	{
		if (s[*index] == '\\' && s[*index + 1])
			(*index)++;
		(*index)++;
	}
	if (s[*index] == end)
	{
		(*index)++;
		return (true);
	}
	return (false);
}
