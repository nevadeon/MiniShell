#include "tools/memory.h"

void	*mem_cpy(void *dest, const void *src, size_t n)
{
	const uint8_t	*s;
	uint8_t			*d;

	if (n != 0 && (dest == src))
		return (dest);
	s = (const uint8_t *)src;
	d = (uint8_t *)dest;
	while (n--)
		*d++ = *s++;
	return (dest);
}
