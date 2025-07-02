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

void	handle_ope(t_ctx *ctx, t_exec_data *data, t_ope *ope, t_exec_fds next)
{
	int	pipe_fd[2];

	if (ope->type == OPE_PIPE)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"));
		execute_ast_recursive(ctx, data, ope->left, (t_exec_fds){
			.fd1 = pipe_fd[OUT],
			.fd2 = next.fd2,
			.to_close = pipe_fd[IN],
		});
		close(pipe_fd[OUT]);
		if (next.fd2 > 0)
			close(next.fd2);
		execute_ast_recursive(ctx, data, ope->right, (t_exec_fds){
			.fd1 = next.fd1,
			.fd2 = pipe_fd[IN],
			.to_close = NO_REDIR,
		});
		if (ope->right->type == NODE_LEAF)
			close(pipe_fd[IN]);
	}
}

// void	handle_ope(t_exec_data *data, t_ope *ope, int std_in, int prev_in)
// {
// 	int	pipe_fd[2];

// 	if (ope->type == OPE_PIPE)
// 	{
// 		if (pipe(pipe_fd) == -1)
// 			return (perror("pipe"));
// 		data->to_close = pipe_fd[IN];
// 		execute_ast_recursive(data, ope->left, pipe_fd[OUT], prev_in);
// 		close(pipe_fd[OUT]);
// 		if (prev_in)
// 			close(prev_in);
// 		data->to_close = NO_REDIR;
// 		execute_ast_recursive(data, ope->right, std_in, pipe_fd[IN]);
// 		if (ope->right->type == NODE_LEAF)
// 			close(pipe_fd[IN]);
// 	}
// }
