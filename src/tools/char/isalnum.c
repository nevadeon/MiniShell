#include "char.h"

int	char_isalnum(int c)
{
	return (char_isalpha(c) || (c >= '0' && c <= '9'));
}
