#include "ast.h"

static void	_print_leaf(t_ast *ast)
{
	t_strlist		*list;
	t_redir_list	*rlist;

	list = ast->s_leaf.func;
	while (list)
	{
		printf("%s", list->content);
		list = list->next;
	}
	rlist = ast->s_leaf.redir_in;
	printf(", redir_in [");
	while (rlist)
	{
		printf("%s", list->content);
		list = list->next;
	}
	printf("], redir_out [");
	rlist = ast->s_leaf.redir_out;
	while (rlist)
	{
		printf("%s", list->content);
		list = list->next;
	}
	printf("]");
	printf("\n");
}

void	print_ast(t_ast *ast, int indent)
{
	static const char	*ope_strings[E_OPE_LAST_INDEX] = {
		"|",
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
