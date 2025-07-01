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
	if (!context->tok_l || !context->tok_l->content)
		return (context->root);
	node = mem_alloc(*ctx->cmd, sizeof(t_ast));
	*node = (t_ast){.type = NODE_BRANCH, .ope.type = OPE_PIPE,};
	if (context->prev_ope)
		node_to_append = context->prev_ope;
	else
		node_to_append = context->prev;
	node->ope.right = node_to_append;
	context->root = node;
	context->prev = node;
	context->prev_ope = node;
	context->tok_l = context->tok_l->next;
	if (!context->tok_l
		|| context->tok_l->content->type == TOK_CONTROL_OPE)
		return (throw_error(ctx, E_UNEXPECTED_TOKEN, "|"), NULL);
	return (_handle_word(ctx, context));
}

static t_ast	*_create_leaf(t_ctx *ctx, t_ast_context *data)
{
	t_ast	*node;

	node = mem_alloc(*ctx->cmd, sizeof(t_ast));
	node->type = NODE_LEAF;
	node->leaf.redir[IN] = NO_REDIR;
	node->leaf.redir[OUT] = NO_REDIR;
	node->leaf.func = NULL;
	while (data->tok_l && (data->tok_l->content->type == TOK_WORD
		|| data->tok_l->content->type == TOK_REDIR_OPE))
	{
		if (data->tok_l->content->type == TOK_WORD)
			lst_add_back((t_list **)&node->leaf.func, \
			(t_list *)lst_new(*ctx->cmd, data->tok_l->content->str));
		else
		{
			if (!handle_redir(ctx, &data->tok_l, node))
				return (NULL);
		}
		if (ctx->last_error_type)
			return (NULL);
		data->tok_l = data->tok_l->next;
	}
	return (node);
}

static t_ast	*_handle_word(t_ctx *ctx, t_ast_context *context)
{
	t_ast	*node;

	if (!context->tok_l || !context->tok_l->content)
		return (context->root);
	node = _create_leaf(ctx, context);
	if (ctx->last_error_type)
		return (NULL);
	if (context->prev && context->prev->type == NODE_LEAF)
	{
		if (!context->prev->ope.left)
			context->prev->ope.left = node;
		if (!context->prev->ope.right)
			context->prev->ope.right = node;
	}
	context->prev = node;
	if (!context->root)
		context->root = node;
	if (!context->tok_l)
		return (context->root);
	return (_handle_ope(ctx, context));
}

t_ast	*create_ast(t_ctx *ctx, t_ast_context *context)
{
	if (!context->tok_l)
		return (context->root);
	if (context->tok_l->content->type == TOK_CONTROL_OPE)
		return (_handle_ope(ctx, context));
	return (_handle_word(ctx, context));
}
