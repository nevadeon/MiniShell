#include "tools/str.h"

char	*str_rchr(const char *s, int c)
{
	int	index;

	index = str_len(s);
	while (index > 0 && s[index] != (unsigned char) c)
		index--;
	if (s[index] == (unsigned char) c)
		return ((char *)(s + index));
	return ((char *)s);
}
