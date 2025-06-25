#include "tools/str.h"

static size_t	_get_length(size_t nb_args, va_list lst)
{
	size_t	index;
	size_t	length;

	index = 0;
	length = 0;
	while (index < nb_args)
	{
		length += str_len(va_arg(lst, char *));
		index++;
	}
	return (length);
}

char	*str_vjoin(t_alloc *alloc, size_t nb_args, ...)
{
	char	*r;
	size_t	length;
	va_list	lst;
	size_t	total;
	char	*arg;

	va_start(lst, nb_args);
	length = _get_length(nb_args, lst);
	va_end(lst);
	r = mem_alloc(alloc, length + 1 * sizeof(char));
	va_start(lst, nb_args);
	total = 0;
	while (nb_args > 0)
	{
		arg = va_arg(lst, char *);
		str_memcpy(r + total, arg, str_len(arg));
		total += str_len(arg);
		nb_args--;
	}
	r[length] = '\0';
	va_end(lst);
	return (r);
}
