#include "allocators/allocator.h"
#include "tools/str.h"

char	*str_extract(t_alloc *alloc, char *s, size_t start, size_t end)
{
	char	*ret;
	size_t	len;

	len = end - start;
	ret = mem_alloc(alloc, len + 1);
	ret = str_memcpy(ret, s + start, len);
	ret[len] = '\0';
	return (ret);
}
