#include "executing.h"

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
