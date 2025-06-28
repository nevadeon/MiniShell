#include "tools/io.h"

size_t	io_dputptr(int fd, void *p)
{
	if (p == NULL)
		return (io_dputstr(fd, "(nil)"));
	io_dputstr(fd, "0x");
	return (io_dputulbase(fd, (size_t) p, HEXA_LOW) + 2);
}
