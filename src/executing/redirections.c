#include "executing.h"

void	handle_redirections(int redir[2], int pipe_out, int pipe_in, int to_close)
{
	assert(redir[IN] > 2 || redir[IN] == NO_REDIR);
	assert(redir[OUT] > 2 || redir[OUT] == NO_REDIR);
	assert(pipe_in > 2 || pipe_in == NO_REDIR);
	assert(pipe_out > 2 || pipe_out == NO_REDIR);
	assert(to_close > 2 || to_close == NO_REDIR);
	if (redir[IN] >= 0)
		dup2(redir[IN], STDIN_FILENO);
	else if (pipe_out >= 0)
		dup2(pipe_out, STDIN_FILENO);
	if (redir[OUT] >= 0)
		dup2(redir[OUT], STDOUT_FILENO);
	else if (pipe_in >= 0)
		dup2(pipe_in, STDOUT_FILENO);
	if (pipe_in >= 0)
		close(pipe_in);
	if (pipe_out >= 0)
		close(pipe_out);
	if (to_close >= 0)
		close(to_close);
}

void	close_redirections(t_ast *ast)
{
	if (ast->type == NODE_LEAF)
	{
		assert(ast->leaf.redir[IN] > 2 || ast->leaf.redir[IN] == NO_REDIR);
		assert(ast->leaf.redir[OUT] > 2 || ast->leaf.redir[OUT] == NO_REDIR);
		if (ast->leaf.redir[IN] > STDERR)
			close(ast->leaf.redir[IN]);
		if (ast->leaf.redir[OUT] > STDERR)
			close(ast->leaf.redir[OUT]);
	}
	else
	{
		close_redirections(ast->ope.left);
		close_redirections(ast->ope.right);
	}
}
