#include "minishell.h"
#include "string.h"

static t_ast	*_create_leaf_by_hand(char *fnc_name, char *arg)
{
	t_ast		*leaf;
	t_str_list	*args;

	leaf = malloc(sizeof(t_ast));
	leaf->type = E_NODE_LEAF;
	leaf->s_leaf.type = E_LEAF_FUNC;
	args = (t_str_list *)lst_new(E_LFT_TASK, strdup(fnc_name));
	lst_add_back((t_list **)&args, lst_new(E_LFT_TASK, strdup(arg)));
	leaf->s_leaf.s_func.args = args;
	return (leaf);
}

t_ast	*create_ast_by_hand()
{
	t_ast	*root;

	root = malloc(sizeof(t_ast));
	root->type = E_NODE_OPE;
	root->s_ope.type = E_OPE_PIPE;
	root->s_ope.left = _create_leaf_by_hand("cat", "a");
	root->s_ope.right = _create_leaf_by_hand("grep", "ok");
	return (root);
}
