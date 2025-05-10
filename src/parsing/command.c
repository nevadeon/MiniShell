#include "ast.h"
#include "executing.h"
#include "parsing.h"

static t_ast_data	*_init_ast_data(char *input)
{
	t_ast_data	*ast_data;

	ast_data = mem_alloc(E_LFT_TASK, 1 * sizeof(t_ast_data));
	ast_data->input = input;
	ast_data->last_ope = NULL;
	ast_data->prev_token = E_TOKEN_INIT;
	ast_data->prev = NULL;
	ast_data->root = NULL;
	return (ast_data);
}

void	handle_command(char *input)
{
	t_ast_data			*data;
	t_ast				*ast;

	data = _init_ast_data(input);
	ast = create_ast(data);
	if (!ast)
		return ;
	print_ast(ast, 0);
	execute_ast(ast);
}
