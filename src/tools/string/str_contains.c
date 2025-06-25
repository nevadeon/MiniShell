#include "tools/str.h"

bool	str_contains(const char *str, const char *substr)
{
	int	i;
	int	j;

	if (!str || !substr)
		return (false);
	if (*substr == '\0')
		return (true);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && substr[j] && str[i + j] == substr[j])
			j++;
		if (substr[j] == '\0')
			return (true);
		i++;
	}
	return (false);
}
