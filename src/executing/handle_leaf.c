#include "executing.h"

static void	_free_exit(t_ctx *ctx)
{
	int	exit_status;

	exit_status = ctx->last_exit_code;
	free_allocator(ctx->cmd);
	free_allocator(ctx->prog);
	exit(exit_status);
}

void	handle_leaf(\
	t_ctx *ctx, t_exec_data *data, t_leaf *leaf, t_exec_fds pipe)
{
	char	**args;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	return (perror("fork"));
	if (pid == 0)
	{
		toggle_signal(ctx, S_CHILD);
		if (!handle_redirections(ctx, leaf->redir_list, pipe))
		{
			close_heredocs(data->root);
			_free_exit(ctx);
		}
		close_heredocs(data->root);
		args = (char **)lst_to_array(*(ctx->cmd), (t_list *)leaf->func);
		execute_command(ctx, data->paths, args);
		_free_exit(ctx);
	}
	else
	{
		lst_add_front((t_list **) &data->processes,
		(t_list *) lst_pid_new(*ctx->cmd, pid));
	}
}

// void	handle_leaf(t_exec_data *data, t_leaf *leaf, int pipe_out, int pipe_in)
// {
// 	char	**args;
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		return (perror("fork"));
// 	if (pid == 0)
// 	{
// 		toggle_signal(data->c, S_CHILD);
// 		handle_redirections(leaf->redir, pipe_out, pipe_in, data->to_close);
// 		args = (char **)lst_to_array(*(data->c->cmd), (t_list *)leaf->func);
// 		close_heredocs(data->root);
// 		execute_command(data->c, data->paths, args);
// 		_free_exit(data->c);
// 	}
// 	else
// 	{
// 		lst_add_front((t_list **) &data->processes,
// 			(t_list *) lst_pid_new(*data->c->cmd, pid));
// 	}
// }
