#include "parsing.h"

int	file_open(const char *pathname, int flags, ...)
{
	struct stat	st;
	int			fd;
	va_list		args;
	mode_t		mode;

	if (flags & O_CREAT)
	{
		va_start(args, flags);
		mode = va_arg(args, mode_t);
		va_end(args);
		fd = open(pathname, flags, mode);
	}
	else
		fd = open(pathname, flags);
	if (fd == -1)
		return (-1);
	if (fstat(fd, &st) == -1)
		return (close(fd), -1);
	if (S_ISDIR(st.st_mode))
		return (close(fd), errno = EISDIR, -1);
	return (fd);
}

static void	_handle_in(t_ctx *ctx, t_token *tok, t_ast *node)
{
	if (node->leaf.redir[IN] != NO_REDIR)
		close (node->leaf.redir[IN]);
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

static void	_handle_trunc(t_ctx *ctx, t_token *tok, t_ast *node)
{
	if (node->leaf.redir[OUT] != NO_REDIR)
		close (node->leaf.redir[OUT]);
	node->leaf.redir[OUT] = file_open(tok->str,
		O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (node->leaf.redir[OUT] == -1)
	{
		if (errno == EISDIR)
			return (throw_error(ctx, E_IS_DIR, tok->str));
		if (errno == EACCES)
			return (throw_error(ctx, E_PERM_DENIED, tok->str));
		return (throw_error(ctx, E_UNKNOWN, tok->str));
	}
}


static void	_handle_append(t_ctx *ctx, t_token *tok, t_ast *node)
{
	if (node->leaf.redir[OUT] != NO_REDIR)
		close (node->leaf.redir[OUT]);
	node->leaf.redir[OUT] = file_open(tok->str,
		O_WRONLY | O_CREAT | O_APPEND,
		0644);
	if (node->leaf.redir[OUT] == -1)
	{
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
	if (!(*tok_l))
		return (throw_error(ctx, E_UNEXPECTED_TOKEN, "newline"), false);
	tok = (*tok_l)->content;
	if (redir_type == E_REDIR_IN)
		_handle_in(ctx, tok, node);
	else if (redir_type == REDIR_HEREDOC)
		handle_heredoc(ctx, tok, node);
	else if (redir_type == E_REDIR_OUT_TRUNC)
		_handle_trunc(ctx, tok, node);
	else if (redir_type == E_REDIR_OUT_APPEND)
		_handle_append(ctx, tok, node);
	if (ctx->last_error_type)
		return (false);
	return (true);
}
