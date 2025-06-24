#include <stdbool.h>

bool	is_blank_meta(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*
 * see : https://www.gnu.org/software///bash/manual/bash.html#Shell-Syntax
 * 
*/
bool	is_meta(char c)
{
	return (is_blank_meta(c) || (c == '|' || c == '<' || c == '>'));
}

// bool	is_meta(char c)
// {
// 	return (is_blank_meta(c) || (c == '|'
// 		|| c == '&' || c == ';' || c == '(' || c == ')' || c == '<'
// 		|| c == ')' || c == '>'));
// }
