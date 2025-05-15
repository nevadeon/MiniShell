#include "ast.h"
#include "str.h"

t_token	get_token_type(char *word)
{
	if (str_equals(word, "|"))
		return (E_TOKEN_OPE);
	if (str_equals(word, ">")
		|| str_equals(word, "<")
		|| str_equals(word, "<<")
		|| str_equals(word, ">>"))
		return (E_TOKEN_REDIR);
	return (E_TOKEN_WORD);
}
