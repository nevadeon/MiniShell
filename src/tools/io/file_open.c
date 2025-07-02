#include "tools/io.h"

int	io_fopen(const char *pathname, int flags, ...)
{
	struct stat	st;
	int			fd;
	va_list		args;
	mode_t		mode;

	if (flags & O_CREAT)
	{
		va_start(args, flags);
		mode = va_arg(args, mode_t);
		va_end(args);
		fd = open(pathname, flags, mode);
	}
	else
		fd = open(pathname, flags);
	if (fd == -1)
		return (-1);
	if (fstat(fd, &st) == -1)
		return (close(fd), -1);
	if (S_ISDIR(st.st_mode))
		return (close(fd), errno = EISDIR, -1);
	return (fd);
}
