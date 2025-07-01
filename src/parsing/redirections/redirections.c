#include "parsing.h"

int	file_open(const char *pathname, int flags)
{
	struct stat	st;
	int			fd;

	fd = open(pathname, flags);
	if (fd == -1)
		return (-1);
	if (fstat(fd, &st) == -1)
	{
		close(fd);
		return (-1);
	}
	if (S_ISDIR(st.st_mode))
	{
		close(fd);
		errno = EISDIR;
		return (-1);
	}
	return (fd);
}

static void	_handle_in(t_ctx *ctx, t_token *tok, t_ast *node)
{
	node->leaf.redir[IN] = file_open(tok->str, O_RDONLY);
	if (node->leaf.redir[IN] == -1)
	{
		if (errno == ENOENT)
			return (throw_error(ctx, E_NO_FILE_OR_DIR, tok->str));
		if (errno == EISDIR)
			return (throw_error(ctx, E_IS_DIR, tok->str));
		if (errno == EACCES)
			return (throw_error(ctx, E_PERM_DENIED, tok->str));
		return (throw_error(ctx, E_UNKNOWN, tok->str));
	}
}


bool	handle_redir(t_ctx *ctx, t_token_list **tok_l, t_ast *node)
{
	t_token			*tok;
	t_redir_type	redir_type;

	tok = (*tok_l)->content;
	assert((tok->type) == TOK_REDIR_OPE);
	redir_type = get_redir_type(tok->str);
	(*tok_l) = (*tok_l)->next;
	tok = (*tok_l)->content;
	if (!tok)
		return (throw_error(ctx, E_UNEXPECTED_TOKEN, "newline"), false);
	if (redir_type == REDIR_IN)
		_handle_in(ctx, tok, node);
	else if (redir_type == REDIR_HEREDOC)
		handle_heredoc(ctx, tok, node);
	// else if (redir_type == REDIR_OUT_TRUNC)
	// 	_handle_trunc();
	// else if (redir_type == REDIR_OUT_APPEND)
	// 	_handle_append();
	if (ctx->last_exit_code)
		return (false);
	return (true);
}
