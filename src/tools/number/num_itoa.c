#include "tools/num.h"

static int	_count_digit(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

char	*num_itoa(t_alloc *alloc, int n)
{
	char	*r;
	int		size;
	long	n_cpy;

	n_cpy = (long)n;
	size = _count_digit(n) + (n < 0);
	r = (char *)mem_alloc(alloc, sizeof(char) * (size + 1));
	if (!r)
		return (NULL);
	r[0] = '-';
	if (n == 0)
		r[0] = '0';
	n_cpy = (long)n;
	if (n_cpy < 0)
		n_cpy = -n_cpy;
	while (size - (n < 0) > 0)
	{
		r[size - 1] = (n_cpy % 10) + '0';
		n_cpy /= 10;
		size--;
	}
	r[_count_digit(n) + (n < 0)] = '\0';
	return (r);
}
