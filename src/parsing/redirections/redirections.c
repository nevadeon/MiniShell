#include "parsing.h"

bool	handle_redir(t_ctx *ctx, t_token_list **tok_l, t_ast *node)
{
	t_token			*tok;
	t_redir_type	redir_type;
	t_redir_list	*redir;
	int				hdoc_fd;

	hdoc_fd = -1;
	tok = (*tok_l)->content;
	assert((tok->type) == TOK_REDIR_OPE);
	redir_type = get_redir_type(tok->str);
	(*tok_l) = (*tok_l)->next;
	if (!(*tok_l))
		return (throw_error(ctx, E_UNEXPECTED_TOKEN, "newline"), false);
	tok = (*tok_l)->content;
	if (get_token_type(tok->str) == TOK_CONTROL_OPE || get_token_type(tok->str) == TOK_REDIR_OPE)
		return (throw_error(ctx, E_UNEXPECTED_TOKEN, tok->str), false);
	if (redir_type == REDIR_HEREDOC)
		hdoc_fd = handle_heredoc(ctx, tok->str);
	redir = mem_alloc(*ctx->cmd, sizeof(t_redir_list));
	if (hdoc_fd == -1)
		*redir = (t_redir_list){.type = redir_type, .filename = tok->str};
	else
		*redir = (t_redir_list){.type = redir_type, .heredoc = hdoc_fd};
	return (lst_add_back((t_list **)&(node->leaf.redir_list), (t_list *)redir), true);
}
