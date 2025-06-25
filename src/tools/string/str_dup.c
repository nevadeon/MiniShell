#include "tools/str.h"

char	*str_dup(t_alloc *alloc, char *s)
{
	char	*r;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = str_len(s);
	r = mem_alloc(alloc, sizeof(char) * (s_len + 1));
	if (!r)
		return (NULL);
	str_memcpy(r, s, s_len);
	r[s_len] = '\0';
	return (r);
}
