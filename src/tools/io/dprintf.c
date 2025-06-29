#include "tools/io.h"

static size_t	_dprintarg(int fd, char c, va_list *args)
{
	if (c == 'c')
		return (io_dputchar(fd, (unsigned char) va_arg(*args, int)));
	else if (c == 's')
		return (io_dputstr(fd, va_arg(*args, char *)));
	else if (c == 'p')
		return (io_dputptr(fd, va_arg(*args, void *)));
	else if (c == 'd' || c == 'i')
		return (io_dputlbase(fd, (long) va_arg(*args, int), DEC));
	else if (c == 'u')
		return (io_dputulbase(fd, (uint64_t) va_arg(*args, uint32_t), DEC));
	else if (c == 'x')
		return (io_dputulbase(fd, (uint64_t) va_arg(*args, uint32_t), HEXA_LOW));
	else if (c == 'X')
		return (io_dputulbase(fd, (uint64_t) va_arg(*args, uint32_t), HEXA_UPP));
	else if (c == '%')
		return (io_dputchar(fd, '%'));
	return (0);
}

size_t	io_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	size_t	nb_printed;

	nb_printed = 0;
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%')
			nb_printed += _dprintarg(fd, *(++format), &args);
		else
			nb_printed += io_dputchar(fd, *format);
		format++;
	}
	va_end(args);
	return (nb_printed);
}
