#include "executing.h"

void	open_heredoc(t_ctx *ctx, t_redir_list *list, t_redir_data *redir)
{
	(void)ctx;
	if (redir->in >= 0 && !redir->is_heredoc)
		close(redir->in);
	redir->in = list->heredoc;
	redir->is_heredoc = true;
}
