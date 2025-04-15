#include "ast.h"
#include "str.h"
#include "mem.h"

t_ast_data	*init_ast_data(char *input)
{
	t_ast_data	*ast_data;

	ast_data = mem_alloc(E_LFT_TASK, 1 * sizeof(t_ast_data));
	ast_data->input = input;
	ast_data->last_ope = NULL;
	ast_data->prev = NULL;
	ast_data->root = NULL;
	return (ast_data);
}

t_node_type	get_node_type(char *word)
{
	if (str_equals(word, "|"))
		return (E_NODE_OPE);
	if (str_equals(word, ">"))
		return (E_NODE_OPE);
	if (str_equals(word, ">>"))
		return (E_NODE_OPE);
	if (str_equals(word, "<"))
		return (E_NODE_OPE);
	if (str_equals(word, "<<"))
		return (E_NODE_OPE);
	return (E_NODE_LEAF);
}

t_ast	*create_ast(t_ast_data *data)
{
	char		*word;
	t_node_type	node_type;

	word = get_next_word(&data->input);
	if (!word || str_len(word) == 0)
		return (data->root);
	node_type = get_node_type(word);
	if (node_type == E_NODE_LEAF)
		return (handle_leaf(data, word));
	if (node_type == E_NODE_OPE)
		return (handle_ope(data, word));
	return (NULL);
}
