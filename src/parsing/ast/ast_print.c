#include "tools/list.h"
#include "parsing.h"

static void	plstr(void *content)
{
	printf("%s", (char *)content);
}

#include <string.h>
static void plredir(t_redir_list *l)
{
	t_redir_list	*current;
	char			*type_str;

	current = l;
	while (current)
	{
		if (current->type == E_REDIR_IN)
			type_str = strdup("<");
		if (current->type == E_REDIR_OUT_APPEND)
			type_str = strdup(">>");
		if (current->type == E_REDIR_OUT_TRUNC)
			type_str = strdup(">");
		if (current->type == E_REDIR_HEREDOC)
			type_str = strdup("<<");
		printf(" %s ", type_str);
		free(type_str);
		printf("%s", (char *)current->content);
		current = current->next;
	}
}

static void	_print_leaf(t_ast *ast)
{
	if (!ast->s_leaf.func)
		return ;
	printf("function : %s", ast->s_leaf.func->content);
	if (ast->s_leaf.func->next)
	{
		printf(" [");
		lst_print((t_list *)ast->s_leaf.func->next, (void (*)(void *))plstr);
		printf("]");
	}
	if (ast->s_leaf.redir_in)
		plredir(ast->s_leaf.redir_in);
	if (ast->s_leaf.redir_out)
		plredir(ast->s_leaf.redir_out);
	printf("\n");
}

void	print_ast(t_ast *ast, int indent)
{
	int	i;

	if (!ast)
		return ;
	i = -1;
	while (++i < indent)
		printf("  ");
	if (ast->type == E_WORD)
		_print_leaf(ast);
	else if (ast->type == E_CONTROL_OPE)
	{
		printf("Operator: |\n");
		print_ast(ast->s_ope.left, indent + 1);
		print_ast(ast->s_ope.right, indent + 1);
	}
}
