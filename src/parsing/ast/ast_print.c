#include "ast.h"
#include "list.h"

void	_print_redir(t_redir_list *list)
{
	static char	*redir_type[E_REDIR_LAST_INDEX] = {
		"<",
		"<<",
		">",
		">>"
	};

	if (list)
	{
		printf("%s ", redir_type[list->type]);
		printf("%s", list->content);
	}
}

static void	_print_strlist(t_strlist *list)
{
	if (list)
		printf("%s", list->content);
}

static void	_print_leaf(t_ast *ast)
{
	if (!ast->s_leaf.func)
		return ;
	printf("function : %s", ast->s_leaf.func->content);
	if (ast->s_leaf.func->next)
	{
		printf(" [");
		lst_print((t_list *)ast->s_leaf.func->next, (void (*)(void *))_print_strlist);
		printf("]");
	}
	if (ast->s_leaf.redir_in)
	{
		printf(", in ");
		lst_print((t_list *)ast->s_leaf.redir_in, (void (*)(void *))_print_redir);
	}
	if (ast->s_leaf.redir_out)
	{
		printf(", out ");
		lst_print((t_list *)ast->s_leaf.redir_out, (void (*)(void *))_print_redir);
	}
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
