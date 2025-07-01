#include "executing.h"

void	handle_redirections(int redir[2], t_fds pipe)
{
	if (redir[IN] > 0)
		dup2(redir[IN], STDIN_FILENO);
	else
		dup2_close(pipe.in, STDIN_FILENO);
	if (redir[OUT] > 0)
		dup2(redir[OUT], STDIN_FILENO);
	else
		dup2_close(pipe.out, STDIN_FILENO);
	if (pipe.to_close > 0)
		close(pipe.to_close);
}

void	close_redirections(t_ast *ast)
{
	if (ast->type == NODE_LEAF)
	{
		if (ast->leaf.redir[IN] > 0)
			close(ast->leaf.redir[IN]);
		if (ast->leaf.redir[OUT] > 0)
			close(ast->leaf.redir[OUT]);
	}
	else
	{
		close_redirections(ast->ope.left);
		close_redirections(ast->ope.right);
	}
}
