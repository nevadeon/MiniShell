#include "ast.h"

static void	_print_args(t_args *current)
{
	if (!current)
		return ;
	printf("%s ", current->content);
	_print_args(current->next);
}

static void	_print_leaf(t_ast *ast)
{
	printf("Leaf -> ");
	if (ast->s_leaf.type == E_LEAF_FILENAME)
		printf("type : filename, name %s", ast->s_leaf.filename);
	else
	{
		printf("type : func, name %s", ast->s_leaf.s_func.cmd);
		if (ast->s_leaf.s_func.nb_args != 0)
			printf(", args [%d]: ", ast->s_leaf.s_func.nb_args);
		_print_args(ast->s_leaf.s_func.args);
	}
	printf("\n");
}

void	print_ast(t_ast *ast, int indent)
{
	static const char	*ope_strings[E_OPE_LAST_INDEX] = {
		"|",
		"<",
		"<<",
		">",
		">>",
	};
	int					i;

	if (!ast)
		return ;
	i = -1;
	while (++i < indent)
		printf("  ");
	if (ast->type == E_NODE_LEAF)
		_print_leaf(ast);
	else if (ast->type == E_NODE_OPE)
	{
		printf("Operator: %s\n", ope_strings[ast->s_ope.type]);
		print_ast(ast->s_ope.left, indent + 1);
		print_ast(ast->s_ope.right, indent + 1);
	}
}
