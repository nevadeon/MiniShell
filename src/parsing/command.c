#include "ast.h"
#include "parsing.h"
#include "executing.h"

static t_ast_context	*_init_ast_context(t_alloc *alloc, char *input)
{
	t_ast_context	*ast_context;

	ast_context = mem_alloc(alloc, 1 * sizeof(t_ast_context));
	ast_context->alloc = alloc;
	ast_context->input = input;
	ast_context->last_ope = NULL;
	ast_context->prev_token = E_TOKEN_INIT;
	ast_context->prev = NULL;
	ast_context->root = NULL;
	return (ast_context);
}

void	handle_command(t_alloc *prog, t_alloc *cmd, char *input)
{
	t_ast_context		*data;
	t_ast				*ast;

	data = _init_ast_context(cmd, input);
	ast = create_ast(data);
	if (!ast)
		return ;
	print_ast(ast, 0);
	execute_ast(prog, cmd, ast);
}
