#include "parsing.h"

bool	is_var_name_valid(char *str)
{
	size_t	index;

	index = 0;
	if ((str)[index] != '_' && !char_isalpha((str)[index]))
		return (false);
	while (char_isalnum((str)[index]) || (str)[index] == '_')
		index++;
	return (index == str_len(str));
}
