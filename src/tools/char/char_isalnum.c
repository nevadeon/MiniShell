#include "char.h"

bool	char_isalnum(char c)
{
	return (char_isalpha(c) || char_isnum(c));
}
