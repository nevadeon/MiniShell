#include "tools/str.h"

int	str_ncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	while (index < n && s1[index] && s2[index] && s1[index] == s2[index])
		index++;
	if (index == n)
		return (0);
	return (s1[index] - s2[index]);
}
