#include "minishell.h"
#include "string.h"

//c'est un fichier pour tester, l'emplacement n'est probablement pas ideal
//ce serait mieux d'avoir ces fonctions dans la partie test probablement
//mais ca rend la compilation reloue avec les commande make actuelles

static t_ast	*_create_leaf_by_hand(int count, ...)
{
	t_ast		*leaf;
	t_strlist	*args;
	va_list		strings;

	leaf = malloc(sizeof(t_ast));
	leaf->type = E_NODE_LEAF;
	leaf->s_leaf.type = E_LEAF_FUNC;

	va_start(strings, count);
	args = (t_strlist *)lst_new(E_LFT_TASK, strdup(va_arg(strings, char *)));
	int i = 0;
	while (++i < count)
		lst_add_back((t_list **)&args, lst_new(E_LFT_TASK, strdup(va_arg(strings, char *))));
	va_end(strings);

	leaf->s_leaf.func = args;
	return (leaf);
}

static t_ast	*_create_ope2_by_hand()
{
	t_ast	*ope;

	ope = malloc(sizeof(t_ast));
	ope->type = E_NODE_OPE;
	ope->s_ope.type = E_OPE_PIPE;
	ope->s_ope.left = _create_leaf_by_hand(1, "cat");
	ope->s_ope.right = _create_leaf_by_hand(2, "grep", "o");
	return (ope);
}

static t_ast	*_create_ope_by_hand()
{
	t_ast	*ope;

	ope = malloc(sizeof(t_ast));
	ope->type = E_NODE_OPE;
	ope->s_ope.type = E_OPE_PIPE;
	ope->s_ope.left = _create_leaf_by_hand(1, "cat");
	ope->s_ope.right = _create_ope2_by_hand();
	return (ope);
}

t_ast	*create_ast_by_hand()
{
	t_ast	*root;

	root = malloc(sizeof(t_ast));
	root->type = E_NODE_OPE;
	root->s_ope.type = E_OPE_PIPE;
	root->s_ope.left = _create_leaf_by_hand(2, "cat", "a");
	// root->s_ope.right = _create_leaf_by_hand(2, "grep", "go");
	root->s_ope.right = _create_ope_by_hand();
	return (root);
}
