#include "tools/str.h"
#include "tools/char.h"

int	str_atoi(const char *s)
{
	int		result;
	int		index;
	bool	positive;

	if (!s)
		return (0);
	if (str_equals(s, "-2147483648"))
		return (-2147483648);
	positive = (s[0] == '-');
	result = 0;
	index = positive;
	while (s[index] && char_isnum(s[index]))
	{
		result *= 10;
		result += s[index] - '0';
		index++;
	}
	return (result);
}
