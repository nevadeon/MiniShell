#include "parsing.h"

static bool	_has_error(t_ast_data *data)
{
	if (data->prev_token == E_TOKEN_REDIR
		|| (data->prev_token == E_TOKEN_LAST_INDEX && data->token == E_TOKEN_OPE)
		|| (data->prev_token == E_TOKEN_OPE && data->token == E_TOKEN_OPE)
		|| (data->prev_token == E_TOKEN_REDIR && data->token == E_TOKEN_OPE))
		return (print_parsing_error(E_ERR_PARSING_UNEXPECTED_TOKEN, data->word), true);
	return (false);
}

t_ast	*create_ast(t_ast_data *data)
{
	char		*word;
	t_token		token;

	word = get_next_word(&data->input);
	if (!word || str_len(word) == 0)
	{
		if (data->prev_token == E_TOKEN_OPE || data->prev_token == E_TOKEN_REDIR)
			return (print_parsing_error(E_ERR_PARSING_UNEXPECTED_TOKEN, data->word), NULL);
		return (data->root);
	}
	token = get_token_type(word);
	data->word = word;
	data->token = token;
	if (_has_error(data))
		return (NULL);
	if (token == E_TOKEN_OPE)
		return (handle_ope(data));
	return (handle_leaf(data));
}
