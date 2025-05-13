#include "str.h"
#include "mem.h"

char	*str_dup(t_lifetime lft, char *s)
{
	char	*r;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = str_len(s);
	r = mem_alloc(lft, sizeof(char) * (s_len + 1));
	str_memcpy(r, s, s_len);
	return (r);
}
