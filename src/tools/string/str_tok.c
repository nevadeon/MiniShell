#include "tools/str.h"

char	*str_tok(t_alloc *alloc, char **str, const char *delim)
{
	int			index;
	char		*ret;
	int			delim_index;

	if (!str)
		return (NULL);
	index = 0;
	ret = str_dup(alloc, *str);
	while ((*str)[index])
	{
		delim_index = -1;
		while (delim[++delim_index])
		{
			if ((*str)[index] == delim[delim_index])
			{
				ret[index] = '\0';
				(*str) += ++index;
				return (ret);
			}
		}
		index++;
	}
	*str = NULL;
	return (ret);
}
