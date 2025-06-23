#include <stdbool.h>

bool	is_a_token(char c)
{
	return (
		!c
		|| c == '|'
		|| c == '>'
		|| c == '<'
		|| c == '\t'
		|| c == ' '
		|| c == '\n'
	);
}
