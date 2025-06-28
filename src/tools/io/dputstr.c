#include "tools/io.h"

size_t	io_dputstr(int fd, const char *s)
{
	size_t	len;

	if (s == NULL)
		return (io_dputstr(fd, "(null)"));
	len = str_len(s);
	write(fd, s, len);
	return (len);
}
