#include "executing.h"

static void	_free_exit(t_ctx *ctx)
{
	int	exit_status;

	exit_status = ctx->last_exit_code;
	free_allocator(ctx->cmd);
	free_allocator(ctx->prog);
	exit(exit_status);
}

void	handle_leaf(t_exec_data *data, t_leaf *leaf, int pipe_out, int pipe_in)
{
	char	**args;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		toggle_signal(data->c, S_CHILD);
		handle_redirections(leaf->redir, pipe_out, pipe_in, data->to_close);
		args = (char **)lst_to_array(*(data->c->cmd), (t_list *)leaf->func);
		close_redirections(data->root);
		execute_command(data->c, data->paths, args);
		_free_exit(data->c);
	}
	else
	{
		lst_add_front((t_list **) &data->processes,
			(t_list *) lst_pid_new(*data->c->cmd, pid));
	}
}
