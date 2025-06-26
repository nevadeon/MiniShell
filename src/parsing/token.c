#include "parsing.h"

t_redir_type	get_redir_type(char *s)
{
	if (str_equals(s, "<<"))
		return (E_REDIR_HEREDOC);
	if (str_equals(s, ">>"))
		return (E_REDIR_OUT_APPEND);
	if (str_equals(s, "<"))
		return (E_REDIR_IN);
	if (str_equals(s, ">"))
		return (E_REDIR_OUT_TRUNC);
	return (E_REDIR_LAST_INDEX);
}

t_token_type	get_token_type(char *s)
{
	if (str_equals(s, "|"))
		return (E_CONTROL_OPE);
	if (str_equals(s, "<<")
		|| str_equals(s, ">>")
		|| str_equals(s, "<")
		|| str_equals(s, ">"))
		return (E_REDIR_OPE);
	return (E_WORD);
}

t_token	*new_token(t_alloc *alloc, char *str, bool expanded, t_token_type type)
{
	t_token	*token;

	token = mem_alloc(alloc, sizeof(t_token));
	token->str = str;
	token->expanded = expanded;
	token->type = type;
	return (token);
}
