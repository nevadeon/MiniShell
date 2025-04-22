#include "ast.h"

static void	_print_args(t_str_list *current)
{
	while (current)
	{
		printf("%s", current->content);
		if (current->next)
			printf(", ");
		current = current->next;
	}
}

static void	_print_leaf(t_ast *ast)
{
	if (ast->s_leaf.type == E_LEAF_FILENAME)
		printf("filename: %s", ast->s_leaf.filename);
	else
	{
		printf("function: %s", ast->s_leaf.s_func.args->content);
		if (ast->s_leaf.s_func.args->next)
		{
			printf(", args [");
			_print_args(ast->s_leaf.s_func.args->next);
			printf("]");
		}
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
