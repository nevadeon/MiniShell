#include "executing.h"

static const t_redir_open_fn	g_redir_open_fn[] = {
[REDIR_IN] = open_input,
[REDIR_HEREDOC] = open_heredoc,
[REDIR_OUT_TRUNC] = open_truncate,
[REDIR_OUT_APPEND] = open_append,
};

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
				g_redir_open_fn[i](ctx, redir_list, &redir);
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

static void	_handle_pipe_redirections(t_exec_fds pipe, t_redir_data *redir)
{
	if (pipe.out >= 0 && redir->in == NO_REDIR && !redir->error)
		dup2(pipe.out, STDIN_FILENO);
	if (pipe.in >= 0 && redir->out == NO_REDIR && !redir->error)
		dup2(pipe.in, STDOUT_FILENO);
	if (pipe.in >= 0)
		close(pipe.in);
	if (pipe.out >= 0)
		close(pipe.out);
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
				g_redir_open_fn[i](ctx, list, &redir);
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
