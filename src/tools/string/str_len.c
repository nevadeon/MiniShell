#include "tools/str.h"

size_t	str_len(const char *str)
{
	size_t	index;

	index = 0;
	while (str && str[index])
		index++;
	return (index);
}
