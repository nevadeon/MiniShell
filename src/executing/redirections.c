#include "executing.h"

typedef void	(*t_redir_handler_fn)(t_ctx *ctx, t_redir_list *list, t_redir_data *redir);

static const t_redir_handler_fn	g_redir_handler_fn[] = {
[REDIR_IN] = handle_in,
[REDIR_HEREDOC] = _handle_heredoc,
[REDIR_OUT_TRUNC] = handle_trunc,
[REDIR_OUT_APPEND] = handle_append,
};

void	_handle_heredoc(t_ctx *ctx, t_redir_list *list, t_redir_data *redir)
{
	(void)ctx;
	if (redir->in >= 0 && !redir->is_heredoc)
		close(redir->in);
	redir->in = list->heredoc;
	redir->is_heredoc = true;
}

void	handle_in(t_ctx *ctx, t_redir_list *list, t_redir_data *redir)
{
	if (redir->in >= 0 && !redir->is_heredoc)
		close(redir->in);
	redir->in = io_fopen(list->filename, O_RDONLY);
	redir->is_heredoc = false;
	if (redir->in == -1)
	{
		redir->error = true;
		if (errno == ENOENT)
			return (throw_error(ctx, E_NO_FILE_OR_DIR, list->filename));
		if (errno == EISDIR)
			return (throw_error(ctx, E_IS_DIR, list->filename));
		if (errno == EACCES)
			return (throw_error(ctx, E_PERM_DENIED, list->filename));
		return (throw_error(ctx, E_UNKNOWN, list->filename));
	}
}

void	handle_trunc(t_ctx *ctx, t_redir_list *list, t_redir_data *redir)
{
	if (redir->out >= 0)
		close(redir->out);
	redir->out = io_fopen(
		list->filename,
		O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
	);
	if (redir->out == -1)
	{
		redir->error = true;
		if (errno == EISDIR)
			return (throw_error(ctx, E_IS_DIR, list->filename));
		if (errno == EACCES)
			return (throw_error(ctx, E_PERM_DENIED, list->filename));
		return (throw_error(ctx, E_UNKNOWN, list->filename));
	}
}

void	handle_append(t_ctx *ctx, t_redir_list *list, t_redir_data *redir)
{
	if (redir->out >= 0)
		close(redir->out);
	redir->out = io_fopen(\
		list->filename,
		O_WRONLY | O_CREAT | O_APPEND,
		0644
	);
	if (redir->out == -1)
	{
		redir->error = true;
		if (errno == EISDIR)
			return (throw_error(ctx, E_IS_DIR, list->filename));
		if (errno == EACCES)
			return (throw_error(ctx, E_PERM_DENIED, list->filename));
		return (throw_error(ctx, E_UNKNOWN, list->filename));
	}
}

static void	_handle_pipe_redirections(t_exec_fds pipe, t_redir_data *redir)
{
	int	pipe_in;
	int	pipe_out;

	pipe_in = pipe.fd2;
	pipe_out = pipe.fd1;
	if (pipe_out >= 0 && redir->in == NO_REDIR && !redir->error)
		dup2(pipe_out, STDIN_FILENO);
	if (pipe_in >= 0 && redir->out == NO_REDIR && !redir->error)
		dup2(pipe_in, STDOUT_FILENO);
	if (pipe_in >= 0)
		close(pipe_in);
	if (pipe_out >= 0)
		close(pipe_out);
	if (pipe.to_close >= 0)
		close(pipe.to_close);
}

bool	handle_redirections(t_ctx *ctx, t_redir_list *list, t_exec_fds pipe)
{
	t_redir_data	redir;
	int				i;

	redir = (t_redir_data){
		.in = NO_REDIR, .out = NO_REDIR, .error = false, .is_heredoc = false};
	while (list && !redir.error)
	{
		i = -1;
		while (++i < REDIR_INDEX_MAX && !redir.error)
			if (i == (int)list->type)
				g_redir_handler_fn[i](ctx, list, &redir);
		list = list->next;
	}
	if (redir.in >= 0 && !redir.error)
		dup2(redir.in, STDIN_FILENO);
	if (redir.out >= 0 && !redir.error)
		dup2(redir.out, STDOUT_FILENO);
	if (redir.in >= 0 && !redir.is_heredoc)
		close(redir.in);
	if (redir.out >= 0)
		close(redir.out);
	_handle_pipe_redirections(pipe, &redir);
	if (redir.error)
		return (false);
	return (true);
}

bool	single_builtin_redirection(
	t_ctx *ctx, t_redir_list *redir_list, int *stdou_cpy, char *cmd_name)
{
	t_redir_data	redir;
	int				i;

	redir = (t_redir_data){
		.in = NO_REDIR, .out = NO_REDIR, .error = false, .is_heredoc = false};
	while (redir_list && !redir.error)
	{
		i = -1;
		while (++i < REDIR_INDEX_MAX && !redir.error)
			if (i == (int)redir_list->type)
				g_redir_handler_fn[i](ctx, redir_list, &redir);
		redir_list = redir_list->next;
	}
	if (redir.out >= 0 && !redir.error && !str_equals(cmd_name, "exit"))
	{
		*stdou_cpy = dup(STDOUT_FILENO);
		dup2(redir.out, STDOUT_FILENO);
	}
	if (redir.in >= 0 && !redir.is_heredoc)
		close(redir.in);
	if (redir.out >= 0)
		close(redir.out);
	if (redir.error)
		return (false);
	return (true);
}

void	close_heredocs(t_ast *ast)
{
	t_redir_list	*redir_list;

	if (ast->type == NODE_LEAF)
	{
		redir_list = ast->leaf.redir_list;
		while (redir_list)
		{
			if (redir_list->type == REDIR_HEREDOC)
				close(redir_list->heredoc);
			redir_list = redir_list->next;
		}
	}
	else
	{
		close_heredocs(ast->ope.left);
		close_heredocs(ast->ope.right);
	}
}
