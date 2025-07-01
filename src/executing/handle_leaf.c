#include "executing.h"

static void	_free_exit(t_ctx *ctx)
{
	int	exit_status;

	exit_status = ctx->last_exit_code;
	free_allocator(ctx->cmd);
	free_allocator(ctx->prog);
	exit(exit_status);
}

void	handle_leaf(t_ctx *ctx, t_exec_data *data, t_leaf *leaf, t_fds pipe_fd)
{
	char	**args;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		toggle_signal(ctx, S_CHILD);
		handle_redirections(leaf->redir, pipe_fd);
		args = (char **)lst_to_array(*(ctx->cmd), (t_list *)leaf->func);
		execute_command(ctx, data->paths, args);
		close_redirections(data->root);
		_free_exit(ctx);
	}
	else
	{
		lst_add_front((t_list **) &data->processes,
			(t_list *) lst_pid_new(*ctx->cmd, pid));
	}
}
