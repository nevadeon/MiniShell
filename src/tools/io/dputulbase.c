#include "tools/io.h"

static size_t	_recursive(int fd, uint64_t ul, char *base, size_t base_len)
{
	size_t	nb_printed;

	nb_printed = 0;
	if (ul >= base_len)
		nb_printed += _recursive(fd, ul / base_len, base, base_len);
	io_dputchar(fd, base[ul % base_len]);
	return (nb_printed + 1);
}

size_t	io_dputulbase(int fd, uint64_t ul, char *base)
{
	size_t	base_len;

	base_len = str_len(base);
	return (_recursive(fd, ul, base, base_len));
}
