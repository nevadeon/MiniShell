#include "executing.h"

void	open_truncate(t_ctx *ctx, t_redir_list *list, t_redir_data *redir)
{
	if (redir->out >= 0)
		close(redir->out);
	redir->out = io_fopen(\
		list->filename, \
		O_WRONLY | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH \
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
