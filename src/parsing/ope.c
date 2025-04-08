#include "ast.h"

static t_ope_type	_string_to_ope_type(char *word)
{
	static const char	*ope_strings[E_OPE_LAST_INDEX] = {
		"|",
		"<",
		"<<",
		">",
		">>"
	};
	size_t				index;

	index = 0;
	while (index < E_OPE_LAST_INDEX)
	{
		if (str_equals(word, ope_strings[index]))
			return ((t_ope_type) index);
		index++;
	}
	return (E_OPE_LAST_INDEX);
}

static t_ast	*_create_ope(char *s)
{
	t_ast	*ope;

	ope = umgc_alloc(E_LFT_FEATURE, 1 * sizeof(t_ast));
	ope->type = E_NODE_OPE;
	ope->s_ope.type = _string_to_ope_type(s);
	ope->s_ope.left = NULL;
	ope->s_ope.right = NULL;
	return (ope);
}

t_ast	*handle_ope(t_ast_data *data, char *word)
{
	t_ast	*ope;

	ope = _create_ope(word);
	if (data->prev && data->prev->type == E_NODE_LEAF)
		ope->s_ope.left = data->root;
	if (ope->s_ope.type == E_OPE_PIPE || !data->root || !data->last_ope
		|| data->root->type == E_NODE_LEAF || data->last_ope->s_ope.right)
		data->root = ope;
	if (data->prev && data->prev->type == E_NODE_OPE)
		data->prev->s_ope.right = ope;
	data->prev = ope;
	data->last_ope = ope;
	return (create_ast(data));
}
