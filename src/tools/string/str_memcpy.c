#include "tools/str.h"

void	*str_memcpy(void *dst, void *src, size_t n)
{
	size_t	index;
	void	*dst_cpy;

	dst_cpy = dst;
	index = 0;
	while (index < n)
	{
		((char *)dst)[index] = ((char *)src)[index];
		index++;
	}
	return (dst_cpy);
}
