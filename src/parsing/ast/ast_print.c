#include "tools/list.h"
#include "parsing.h"
#include <string.h>

static void	plstr(void *content)
{
	printf("%s", (char *)content);
}

static void	predir(t_ast *ast)
{

	printf(", in: %d", ast->leaf.redir[IN]);
	// char *line;
	// t_alloc *t = new_arena_allocator(ARENA_BLOCK_SIZE);
	// printf("\ncontenu : ");
	// while ((line = str_gnl(t, ast->leaf.redir[IN])) != NULL)
	// 	printf("%s", line);
	// printf("\n");
	// free_allocator(&t);
	printf(" out: %d", ast->leaf.redir[OUT]);
}

static void	_print_leaf(t_ast *ast)
{
	if (!ast->leaf.func)
		return ;
	printf("function : %s", ast->leaf.func->content);
	if (ast->leaf.func->next)
	{
		printf(" [");
		lst_print((t_list *)ast->leaf.func->next, (void (*)(void *))plstr);
		printf("]");
	}
	predir(ast);
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
	if (ast->type == TOK_WORD)
		_print_leaf(ast);
	else if (ast->type == TOK_CONTROL_OPE)
	{
		printf("Operator: |\n");
		print_ast(ast->ope.left, indent + 1);
		print_ast(ast->ope.right, indent + 1);
	}
}
