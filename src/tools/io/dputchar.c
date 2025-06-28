#include "tools/io.h"

size_t	io_dputchar(int fd, char c)
{
	write(fd, &c, 1);
	return (1);
}
