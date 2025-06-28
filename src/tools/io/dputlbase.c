#include "tools/io.h"

static size_t	_recursive(int fd, size_t l, char *base, size_t base_len)
{
	size_t	nb_printed;

	nb_printed = 0;
	if (l >= base_len)
		nb_printed = _recursive(fd, l / base_len, base, base_len);
	io_dputchar(fd, base[l % base_len]);
	return (nb_printed + 1);
}

size_t	io_dputlbase(int fd, long l, char *base)
{
	size_t	base_len;

	base_len = str_len(base);
	if (l < 0)
	{
		io_dputchar(fd, '-');
		l *= -1;
		return (_recursive(fd, (size_t) l, base, base_len) + 1);
	}
	return (_recursive(fd, (size_t) l, base, base_len));
}
