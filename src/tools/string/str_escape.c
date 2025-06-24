#include "str.h"

bool	str_escape(char *s, size_t *index, char start, char end)
{
	assert(s);
	if (!s[*index])
		return (false);
	if (s[*index] == start)
	{
		while (s[++*index] && s[*index] != end)
			;
		if (s[*index] == end)
			(*index)++;
	}
	return (true);
}
