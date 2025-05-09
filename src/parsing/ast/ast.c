#include "ast.h"
#include "str.h"
#include "mem.h"

t_ast_data	*init_ast_data(char *input)
{
	t_ast_data	*ast_data;

	ast_data = mem_alloc(E_LFT_TASK, 1 * sizeof(t_ast_data));
	ast_data->input = input;
	ast_data->last_ope = NULL;
	ast_data->prev_token = E_TOKEN_LAST_INDEX;
	ast_data->prev = NULL;
	ast_data->root = NULL;
	return (ast_data);
}

t_ast	*create_ast(t_ast_data *data)
{
	char		*word;
	t_token		token;

	word = get_next_word(&data->input);
	if (!word || str_len(word) == 0)
		return (data->root);
	token = get_token_type(word);
	data->token = token;
	if (data->prev_token == E_TOKEN_REDIR)
		exit(EXIT_FAILURE);
	if (data->prev_token == E_TOKEN_LAST_INDEX && data->token == E_TOKEN_OPE)
		exit(EXIT_FAILURE);
	if (data->prev_token == E_TOKEN_OPE && data->token == E_TOKEN_OPE)
		exit(EXIT_FAILURE);
	if (token == E_TOKEN_OPE)
		return (handle_ope(data, word));
	return (handle_leaf(data, word));
}
