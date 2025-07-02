#include "executing.h"

void	open_input(t_ctx *ctx, t_redir_list *list, t_redir_data *redir)
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
