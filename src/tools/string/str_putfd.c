#include "tools/str.h"

size_t	str_putfd(const char *s, int fd)
{
	size_t	len;

	if (s == NULL)
		return (str_putfd("(null)", fd));
	len = str_len(s);
	write(fd, s, len);
	return (len);
}
