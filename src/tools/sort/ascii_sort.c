#include "tools/sort.h"
#include <ctype.h>

int	ascii_sort(void *a, void *b)
{
	const char	*str1;
	const char	*str2;

	str1 = (const char *)a;
	str2 = (const char *)b;
	return (str_cmp(str1, str2));
}

static unsigned char	ascii_tolower_uc(unsigned char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

static int	ascii_cmp_char(unsigned char a, unsigned char b)
{
	unsigned char	la;
	unsigned char	lb;

	la = ascii_tolower_uc(a);
	lb = ascii_tolower_uc(b);
	if (la < lb)
		return (-1);
	if (la > lb)
		return (+1);
	if (a != b)
	{
		if (a >= 'a' && a <= 'z' && b >= 'A' && b <= 'Z')
			return (-1);
		if (a >= 'A' && a <= 'Z' && b >= 'a' && b <= 'z')
			return (+1);
		return ((int)a - (int)b);
	}
	return (0);
}

int	ascii_lexic_cmd(const char *pa, const char *pb)
{
	unsigned char	a;
	unsigned char	b;
	int				cmp;

	while (*pa && *pb)
	{
		a = (unsigned char)*pa;
		b = (unsigned char)*pb;
		cmp = ascii_cmp_char(a, b);
		if (cmp != 0)
			return (cmp);
		pa++;
		pb++;
	}
	return ((int)(unsigned char)*pa - (int)(unsigned char)*pb);
}
