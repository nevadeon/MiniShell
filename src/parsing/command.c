#include "ast.h"
#include "executing.h"
#include "parsing.h"

static t_ast_context	*_init_ast_context(char *input)
{
	t_ast_context	*ast_context;

	ast_context = mem_alloc(E_LFT_TASK, 1 * sizeof(t_ast_context));
	ast_context->input = input;
	ast_context->last_ope = NULL;
	ast_context->prev_token = E_TOKEN_INIT;
	ast_context->prev = NULL;
	ast_context->root = NULL;
	return (ast_context);
}

void	handle_command(char *input)
{
	t_ast_context		*data;
	t_ast				*ast;

	data = _init_ast_context(input);
	ast = create_ast(data);
	if (!ast)
		return ;
	print_ast(ast, 0);
	execute_ast(ast);
}
