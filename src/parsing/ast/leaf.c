#include "ast.h"

static inline bool _is_filename(t_ast *node)
{
	return (
		node
		&& node->type == E_NODE_OPE && node->s_ope.type != E_OPE_PIPE
		&& (
			!node->s_ope.left ||
			node->s_ope.left->type != E_NODE_LEAF ||
			node->s_ope.left->s_leaf.type != E_LEAF_FILENAME
		)
	);
}

static t_ast	*_create_leaf(char *s, t_ast *prev)
{
	t_ast	*leaf;

	leaf = mem_alloc(E_LFT_TASK, 1 * sizeof(t_ast));
	leaf->type = E_NODE_LEAF;
	if (_is_filename(prev))
	{
		leaf->s_leaf.type = E_LEAF_FILENAME;
		leaf->s_leaf.filename = s;
	}
	else
	{
		leaf->s_leaf.type = E_LEAF_FUNC;
		leaf->s_leaf.s_func.cmd = s;
		leaf->s_leaf.s_func.nb_args = 0;
		leaf->s_leaf.s_func.args = NULL;
	}
	return (leaf);
}

static t_ast	*_add_arg(t_ast *prev, char *word)
{
	t_args	*current;

	prev->s_leaf.s_func.nb_args++;
	if (!prev->s_leaf.s_func.args)
	{
		prev->s_leaf.s_func.args = mem_alloc(E_LFT_TASK, 1 * sizeof(t_args));
		prev->s_leaf.s_func.args->next = NULL;
		prev->s_leaf.s_func.args->content = word;
		return (prev);
	}
	current = prev->s_leaf.s_func.args;
	while (current->next)
		current = current->next;
	current->next = mem_alloc(E_LFT_TASK, 1 * sizeof(t_args));
	current->next->next = NULL;
	current->next->content = word;
	return (prev);
}

static inline bool	_is_arg(t_ast_data *data)
{
	return (data && data->prev && data->prev->type == E_NODE_LEAF
		&& data->prev->s_leaf.type == E_LEAF_FUNC);
}

t_ast	*handle_leaf(t_ast_data *data, char *word)
{
	t_ast	*leaf;

	if (_is_arg(data))
	{
		_add_arg(data->prev, word);
		return (create_ast(data));
	}
	leaf = _create_leaf(word, data->prev);
	if (data && !data->prev)
		data->root = leaf;
	if (data->last_ope && !data->last_ope->s_ope.left)
		data->last_ope->s_ope.left = leaf;
	else if (data->last_ope && !data->last_ope->s_ope.right)
		data->last_ope->s_ope.right = leaf;
	data->prev = leaf;
	return (create_ast(data));
}
