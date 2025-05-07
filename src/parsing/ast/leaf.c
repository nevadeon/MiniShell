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
	func = mem_alloc(E_LFT_TASK, sizeof(t_strlist));
	func->content = word;
	func->next = NULL;
	lst_add_back((t_list **)&leaf->s_leaf.func, (t_list *)func);
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

void	handle_leaf(t_ast_data *data, char *word)
{
	t_redir_type	type;
	t_redir_list	*redir_list;
	t_ast			*leaf;

	type = _is_redir(word);
	if (type != E_REDIR_LAST_INDEX)
	{
		redir_list = mem_alloc(E_LFT_TASK, sizeof(t_redir_list));
		redir_list->content = get_next_word(&data->input);
		redir_list->next = NULL;
		redir_list->type = type;
		if (type == E_REDIR_HEREDOC || type == E_REDIR_IN)
			lst_add_front((t_list **)data->prev->s_leaf.redir_in, (t_list *)redir_list);
		else
			lst_add_front((t_list **)data->prev->s_leaf.redir_out, (t_list *)redir_list);
	}
	else
		leaf = _create_leaf(word);
	if (!data->prev)
		data->root = leaf;
	data->prev = leaf;
	create_ast(data);
}
