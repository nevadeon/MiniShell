#include "sort.h"
#include "str.h"

int	ascii_sort(void *a, void *b)
{
	const char	*str1;
	const char	*str2;

	str1 = (const char *)a;
	str2 = (const char *)b;
	return (str_cmp(str1, str2));
}
