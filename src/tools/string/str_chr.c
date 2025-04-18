#include "str.h"

char	*str_chr(const char *s, int c)
{
	while ((unsigned char) *s != (unsigned char) c && *s)
		s++;
	if ((unsigned char) *s == (unsigned char) c)
		return ((char *) s);
	return (NULL);
}
