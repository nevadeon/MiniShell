#include "tools/str.h"

bool	str_equals(const char *str1, const char *str2)
{
	size_t	index;

	index = 0;
	while (str1[index] && str2[index] && str1[index] == str2[index])
		index++;
	return (str1[index] == str2[index]);
}
