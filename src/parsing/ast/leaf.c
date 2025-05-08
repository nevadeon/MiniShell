#include "ast.h"
#include "mem.h"
#include "list.h"
#include "str.h"

static t_ast	*_create_leaf(char *word)
{
	t_ast		*leaf;
	t_strlist	*func;

	leaf = mem_alloc(E_LFT_TASK, sizeof(t_ast));
	leaf->type = E_NODE_LEAF;
	leaf->s_leaf.func = NULL;
	if (word != NULL)
	{
		func = mem_alloc(E_LFT_TASK, sizeof(t_strlist));
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

static void	_handle_redir(t_ast_data *data, char *word, t_redir_type type)
{
	t_redir_list	*redir_list;

	redir_list = mem_alloc(E_LFT_TASK, sizeof(t_redir_list));
	redir_list->content = get_next_word(&data->input);
	redir_list->next = NULL;
	redir_list->type = type;
	if (type == E_REDIR_HEREDOC || type == E_REDIR_IN)
		lst_add_back((t_list **)&data->prev->s_leaf.redir_in, (t_list *)redir_list);
	else
		lst_add_back((t_list **)&data->prev->s_leaf.redir_out, (t_list *)redir_list);
}

static void	_handle_prev_leaf(t_ast_data *data, char *word)
{
	t_strlist	*arg;

	arg = mem_alloc(E_LFT_TASK, sizeof(t_strlist));
	arg->content = word;
	arg->next = NULL;
	lst_add_back((t_list **)&data->prev->s_leaf.func, (t_list *)arg);
}

static void	_handle_leaf_parent(t_ast_data *data, t_ast *leaf)
{
	if (data->prev->type == E_NODE_OPE)
	{
		if (!data->prev->s_ope.left)
			data->prev->s_ope.left = leaf;
		else if (!data->prev->s_ope.right)
			data->prev->s_ope.right = leaf;
	}
}

void	handle_leaf(t_ast_data *data, char *word)
{
	t_redir_type	type;
	t_ast			*leaf;

	if (!data->prev)
	{
		leaf = _create_leaf(NULL);
		data->prev = leaf;
	}
	type = _is_redir(word);
	if (type != E_REDIR_LAST_INDEX)
		_handle_redir(data, word, type);
	else if (data->prev && data->prev->type == E_NODE_LEAF)
	{
		_handle_prev_leaf(data, word);
		leaf = data->prev;
	}
	else
	{
		leaf = _create_leaf(word);
		_handle_leaf_parent(data, leaf);
		data->prev = leaf;
	}
	if (!data->root)
		data->root = leaf;
	create_ast(data);
}
