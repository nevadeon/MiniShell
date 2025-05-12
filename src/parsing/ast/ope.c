#include "ast.h"
#include "str.h"
#include "mem.h"

static t_ope_type	_string_to_ope_type(char *word)
{
	static const char	*ope_strings[E_OPE_LAST_INDEX] = {
		"|",
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

	ope = mem_alloc(E_LFT_TASK, 1 * sizeof(t_ast));
	ope->type = E_NODE_OPE;
	ope->s_ope.type = _string_to_ope_type(s);
	ope->s_ope.left = NULL;
	ope->s_ope.right = NULL;
	return (ope);
}

t_ast	*handle_ope(t_ast_context *data)
{
	t_ast	*ope;

	ope = _create_ope(data->word);
	if (data->prev_token & E_TOKEN_LEAF)
		ope->s_ope.right = data->root;
	if (!data->root || !data->last_ope
		|| data->root->type == E_NODE_LEAF || data->last_ope->s_ope.right)
		data->root = ope;
	if (data->prev_token == E_TOKEN_OPE)
		data->prev->s_ope.left = ope;
	data->prev = ope;
	data->last_ope = ope;
	data->prev_token = data->token;
	return (create_ast(data));
}
