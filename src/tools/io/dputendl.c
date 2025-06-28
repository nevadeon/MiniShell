#include "tools/io.h"

void	io_dputendl(int fd, const char *s)
{
	size_t	len;

	len = str_len(s);
	write(fd, s, len);
	io_dputchar(fd, '\n');
}
