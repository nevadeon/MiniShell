#include "parsing.h"

bool	is_ope(char c)
{
	return (is_control(c) || is_redir(c));
}

bool	is_control(char c)
{
	return (c == '|');
}

bool	is_redir(char c)
{
	return (c == '<' || c == '>');
}
