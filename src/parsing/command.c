#include "ast.h"
#include "executing.h"
#include "error.h"
#include "parsing.h"

void	handle_command(char *input)
{
	t_ast_data			*data;
	t_ast				*ast;
	t_error_code		error_code;
	t_error_category	error_cat;

	error_cat = get_parsing_category();
	error_code = make_error(E_ERR_PARSING_MISSING_OPERAND, &error_cat);
	printf("[%s] %s\n", error_name(&error_code), error_message(&error_code));
	data = init_ast_data(input);
	ast = create_ast(data);
	if (data->prev_token == E_TOKEN_OPE)
		exit(EXIT_FAILURE);
	if (data->prev_token == E_TOKEN_REDIR)
		exit(EXIT_FAILURE);
	print_ast(ast, 0);
	execute_ast(ast);
	// print_ast(create_ast_by_hand(), 0);
	// execute_ast(create_ast_by_hand());
}
