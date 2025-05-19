#include "ast.h"
#include "parsing.h"

static t_ast	*_create_leaf(t_allocator *alloc, char *word)
{
	t_ast		*leaf;
	t_str_list	*func;

	leaf = mem_alloc(alloc, sizeof(t_ast));
	leaf->type = E_NODE_LEAF;
	leaf->s_leaf.func = NULL;
	if (word != NULL)
	{
		func = mem_alloc(alloc, sizeof(t_str_list));
		func->content = word;
		func->next = NULL;
		lst_add_back((t_list **)&leaf->s_leaf.func, (t_list *)func);
	}
	return (leaf);
}

static t_redir_type	_is_redir(char *word)
{
	if (str_equals(word, ">"))
		return (E_REDIR_OUT_TRUNC);
	if (str_equals(word, ">>"))
		return (E_REDIR_OUT_APPEND);
	if (str_equals(word, "<"))
		return (E_REDIR_IN);
	if (str_equals(word, "<<"))
		return (E_REDIR_HEREDOC);
	return (E_REDIR_LAST_INDEX);
}

static bool	_handle_redir(t_ast_context *data, t_redir_type type)
{
	t_redir_list	*redir_list;
	char			*filename;

	redir_list = mem_alloc(data->alloc, sizeof(t_redir_list));
	filename = get_next_word(data->alloc, &data->input);
	if (str_len(filename) != 0)
		data->token = get_token_type(filename);
	if (data->token == E_TOKEN_OPE)
		return (print_parsing_error(E_ERR_PARSING_UNEXPECTED_TOKEN, filename), false);
	redir_list->content = filename;
	redir_list->next = NULL;
	redir_list->type = type;
	if (type == E_REDIR_HEREDOC || type == E_REDIR_IN)
		lst_add_front((t_list **)&data->prev->s_leaf.redir_in, (t_list *)redir_list);
	else
		lst_add_front((t_list **)&data->prev->s_leaf.redir_out, (t_list *)redir_list);
	return (true);
}

static void	_handle_prev_leaf(t_ast_context *data, char *word)
{
	t_str_list	*arg;

	arg = mem_alloc(data->alloc, sizeof(t_str_list));
	arg->content = word;
	arg->next = NULL;
	lst_add_back((t_list **)&data->prev->s_leaf.func, (t_list *)arg);
}

static void	_handle_leaf_parent(t_ast_context *data, t_ast *leaf)
{
	if (data->prev_token == E_TOKEN_OPE)
	{
		if (!data->prev->s_ope.right)
			data->prev->s_ope.right = leaf;
		else if (!data->prev->s_ope.left)
			data->prev->s_ope.left = leaf;
	}
}

t_ast	*handle_leaf(t_ast_context *data)
{
	t_redir_type	type;
	t_ast			*leaf;

	if (!data->prev_token || data->prev_token == E_TOKEN_OPE)
	{
		leaf = _create_leaf(data->alloc, NULL);
		if (data->prev_token == E_TOKEN_OPE)
			_handle_leaf_parent(data, leaf);
		data->prev = leaf;
	}
	type = _is_redir(data->word);
	if (type != E_REDIR_LAST_INDEX)
	{
		if (!_handle_redir(data, type))
			return (NULL);
	}
	else if (data->prev && data->prev->type == E_NODE_LEAF)
	{
		_handle_prev_leaf(data, data->word);
		leaf = data->prev;
	}
	else
	{
		leaf = _create_leaf(data->alloc, data->word);
		_handle_leaf_parent(data, leaf);
		data->prev = leaf;
	}
	if (!data->root)
		data->root = leaf;
	data->prev_token = data->token;
	return (create_ast(data));
}
