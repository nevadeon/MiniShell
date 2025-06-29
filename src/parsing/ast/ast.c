#include "parsing.h"

static t_ast	*_handle_ope(t_ctx *ctx, t_ast_context *context);
static t_ast	*_handle_word(t_ctx *ctx, t_ast_context *context);

static t_ast	*_handle_ope(t_ctx *ctx, t_ast_context *context)
{
	t_ast	*node;
	t_ast	*node_to_append;

	if (!context->root)
		return (throw_error(ctx, E_UNEXPECTED_TOKEN, "|"), NULL);
	node_to_append = NULL;
	if (!context->token_list_item || !context->token_list_item->content)
		return (context->root);
	node = mem_alloc(*ctx->cmd, sizeof(t_ast));
	*node = (t_ast){.type = E_CONTROL_OPE, .s_ope.type = E_OPE_PIPE,};
	if (context->prev_ope)
		node_to_append = context->prev_ope;
	else
		node_to_append = context->prev;
	node->s_ope.right = node_to_append;
	context->root = node;
	context->prev = node;
	context->prev_ope = node;
	context->token_list_item = context->token_list_item->next;
	if (!context->token_list_item
		|| context->token_list_item->content->type == E_CONTROL_OPE)
		return (throw_error(ctx, E_UNEXPECTED_TOKEN, "|"), NULL);
	return (_handle_word(ctx, context));
}

static void	_handle_redir(t_ctx *ctx, t_ast_context *context, t_ast *node)
{
	t_redir_list	*redir;

	redir = mem_alloc(*ctx->cmd, sizeof(t_redir_list));
	redir->content = NULL;
	redir->next = NULL;
	redir->type = get_redir_type(context->token_list_item->content->str);
	context->token_list_item = context->token_list_item->next;
	if (!context->token_list_item)
		return (throw_error(ctx, E_UNEXPECTED_TOKEN, "newline"));
	if (context->token_list_item->content->type == E_CONTROL_OPE)
		return (throw_error(ctx, E_UNEXPECTED_TOKEN, "|"));
	redir->content = context->token_list_item->content->str;
	if (redir->type == E_REDIR_IN || redir->type == E_REDIR_HEREDOC)
		lst_add_back((t_list **)&node->s_leaf.redir_in, (t_list *)redir);
	if (redir->type == E_REDIR_OUT_APPEND || redir->type == E_REDIR_OUT_TRUNC)
		lst_add_back((t_list **)&node->s_leaf.redir_out, (t_list *)redir);
}

static t_ast	*_create_leaf(t_ctx *ctx, t_ast_context *data)
{
	t_ast	*node;

	node = mem_alloc(*ctx->cmd, sizeof(t_ast));
	node->type = E_WORD;
	node->s_leaf.redir_in = NULL;
	node->s_leaf.redir_out = NULL;
	node->s_leaf.func = NULL;
	while (data->token_list_item
		&& (data->token_list_item->content->type == E_WORD
			|| data->token_list_item->content->type == E_REDIR_OPE))
	{
		if (data->token_list_item->content->type == E_WORD)
			lst_add_back((t_list **)&node->s_leaf.func, \
			(t_list *)lst_new(*ctx->cmd, data->token_list_item->content->str));
		else
			_handle_redir(ctx, data, node);
		if (ctx->last_error_type)
			return (NULL);
		data->token_list_item = data->token_list_item->next;
	}
	return (node);
}

static t_ast	*_handle_word(t_ctx *ctx, t_ast_context *context)
{
	t_ast	*node;

	if (!context->token_list_item || !context->token_list_item->content)
		return (context->root);
	node = _create_leaf(ctx, context);
	if (ctx->last_error_type)
		return (NULL);
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
	return (_handle_ope(ctx, context));
}

t_ast	*create_ast(t_ctx *ctx, t_ast_context *context)
{
	if (!context->token_list_item)
		return (context->root);
	if (context->token_list_item->content->type == E_CONTROL_OPE)
		return (_handle_ope(ctx, context));
	return (_handle_word(ctx, context));
}
