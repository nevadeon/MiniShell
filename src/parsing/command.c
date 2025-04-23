#include "ast.h"
#include "executing.h"

void	handle_command(char *input)
{
	t_ast_data	*data;
	t_ast		*ast;

	data = init_ast_data(input);
	ast = create_ast(data);
	print_ast(ast, 0);
	execute_ast(ast);
	// print_ast(create_ast_by_hand(), 0);
	// execute_ast(create_ast_by_hand());
}
