#include "parsing.h"

static t_ast	*_handle_ope(t_alloc *alloc, t_ast_context *context);
static t_ast	*_handle_word(t_alloc *alloc, t_ast_context *context);

static t_ast	*_handle_ope(t_alloc *alloc, t_ast_context *context)
{
	t_ast	*node;
	t_ast	*node_to_append;

	node_to_append = NULL;
	if (!context->token_list_item || !context->token_list_item->content)
		return (context->root);
	node = mem_alloc(alloc, sizeof(t_ast));
	node->type = E_CONTROL_OPE;
	node->s_ope.left = NULL;
	node->s_ope.right = NULL;
	node->s_ope.type = E_OPE_PIPE;
	if (context->prev_ope)
		node_to_append = context->prev_ope;
	else
		node_to_append = context->prev;
	node->s_ope.right = node_to_append;
	context->root = node;
	context->prev = node;
	context->prev_ope = node;
	context->token_list_item = context->token_list_item->next;
	if (!context->token_list_item || context->token_list_item->content->type == E_CONTROL_OPE)
		return (toggle_pars_err(E_PARS_UNEX_TOKEN, "|"), NULL);
	return (_handle_word(alloc, context));
}

static void	_handle_redir(t_alloc *alloc, t_ast_context *context, t_ast *node)
{
	t_redir_list	*redir;

	redir = mem_alloc(alloc, sizeof(t_redir_list));
	redir->content = NULL;
	redir->next = NULL;
	redir->type = get_redir_type(context->token_list_item->content->str);
	context->token_list_item = context->token_list_item->next;
	if (!context->token_list_item)
		return (toggle_pars_err(E_PARS_UNEX_TOKEN, "newline"));
	redir->content = context->token_list_item->content->str;
	if (redir->type == E_REDIR_IN || redir->type == E_REDIR_HEREDOC)
		lst_add_back((t_list **)&node->s_leaf.redir_in, (t_list *)redir);
	if (redir->type == E_REDIR_OUT_APPEND || redir->type == E_REDIR_OUT_TRUNC)
		lst_add_back((t_list **)&node->s_leaf.redir_out, (t_list *)redir);
}

static t_ast	*_create_leaf(t_alloc *alloc, t_ast_context *context)
{
	t_ast	*node;

	node = mem_alloc(alloc, sizeof(t_ast));
	node->type = E_WORD;
	node->s_leaf.redir_in = NULL;
	node->s_leaf.redir_out = NULL;
	node->s_leaf.func = NULL;
	while (context->token_list_item
		&& (context->token_list_item->content->type == E_WORD
			|| context->token_list_item->content->type == E_REDIR_OPE))
	{
		if (context->token_list_item->content->type == E_WORD)
			lst_add_back((t_list **)&node->s_leaf.func, \
			(t_list *)lst_new(alloc, context->token_list_item->content->str));
		else
			_handle_redir(alloc, context, node);
		if (errno)
			return (NULL);
		context->token_list_item = context->token_list_item->next;
	}
	return (node);
}

static t_ast	*_handle_word(t_alloc *alloc, t_ast_context *context)
{
	t_ast	*node;

	if (!context->token_list_item || !context->token_list_item->content)
		return (context->root);
	node = _create_leaf(alloc, context);
	if (context->prev && context->prev->type == E_CONTROL_OPE)
	{
		if (!context->prev->s_ope.left)
			context->prev->s_ope.left = node;
		if (!context->prev->s_ope.right)
			context->prev->s_ope.right = node;
	}
	context->prev = node;
	if (!context->root)
		context->root = node;
	if (!context->token_list_item)
		return (context->root);
	return (_handle_ope(alloc, context));
}

t_ast	*create_ast(t_alloc *alloc, t_ast_context *context)
{
	if (!context->token_list_item)
		return (context->root);
	if (context->token_list_item->content->type == E_CONTROL_OPE)
		return (_handle_ope(alloc, context));
	return (_handle_word(alloc, context));
}
