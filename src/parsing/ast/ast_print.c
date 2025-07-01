#include "tools/list.h"
#include "parsing.h"
#include <string.h>

static void	plstr(void *content)
{
	printf("%s", (char *)content);
}

static void	predir(t_ast *ast, int fds[2])
{
	char	path[PATH_MAX + 1];
	char	resolved_path[PATH_MAX + 1];
	ssize_t	len;

	snprintf(path, sizeof(path), "/proc/self/fd/%d", fds[IN]);
	len = readlink(path, resolved_path, sizeof(resolved_path) - 1);
	if (len == -1) {
		perror("readlink");
		return;
	}
	resolved_path[len] = '\0';
	printf(", in %s (fd: %d)", resolved_path, ast->leaf.redir[IN]);

	snprintf(path, sizeof(path), "/proc/self/fd/%d", fds[OUT]);
	len = readlink(path, resolved_path, sizeof(resolved_path) - 1);
	if (len == -1) {
		perror("readlink");
		return;
	}
	resolved_path[len] = '\0';
	printf(" out %s (fd: %d)", resolved_path, fds[OUT]);
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
	predir(ast, ast->leaf.redir);
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
