#include "executing.h"

/** prompt: `cmd 1 | cmd 2 | cmd 3`
 *
 *  ast:                | (pipe)
 *                     / \
 *                    3   | (pipe)
 *                       / \
 *                      2   1
 *
 * a pipe is created at every pipe branch in the ast. The t_fds struct is
 * used to properly chose which fd will be used as stdin or stdout for the
 * next command
 */

void	handle_ope(t_ctx *ctx, t_exec_data *data, t_ope *ope, t_exec_fds prev)
{
	int	pipe_fd[2];

	if (ope->type == OPE_PIPE)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"));
		execute_ast_recursive(ctx, data, ope->left, (t_exec_fds){
			.out = pipe_fd[OUT],
			.in = prev.in,
			.to_close = pipe_fd[IN],
		});
		close(pipe_fd[OUT]);
		if (prev.in > 0)
			close(prev.in);
		execute_ast_recursive(ctx, data, ope->right, (t_exec_fds){
			.out = prev.out,
			.in = pipe_fd[IN],
			.to_close = NO_REDIR,
		});
		if (ope->right->type == NODE_LEAF)
			close(pipe_fd[IN]);
	}
}
