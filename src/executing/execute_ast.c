#include "minishell.h"

static void	_exec_ast(t_ctx *ctx, t_exec_data *data, t_ast *ast, t_fds fds);

static void	_clean_exit(t_ctx *ctx)
{
	int	exit_status;

	exit_status = ctx->last_exit_code;
	free_allocator(ctx->cmd);
	free_allocator(ctx->prog);
	exit(exit_status);
}

static void	_handle_leaf(\
	t_ctx *ctx, t_exec_data *data, t_leaf *leaf, t_fds pipe_fd)
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
		_clean_exit(ctx);
	}
	else
	{
		lst_add_front((t_list **) &data->processes,
			(t_list *) lst_pid_new(*ctx->cmd, pid));
	}
}

static void	_handle_ope(t_ctx *ctx, t_exec_data *data, t_ope *ope, t_fds fds)
{
	int	pipe_fd[2];

	if (ope->type == OPE_PIPE)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"));
		_exec_ast(ctx, data, ope->left, (t_fds){
			.in = pipe_fd[OUT],
			.out = fds.prev,
			.prev = pipe_fd[IN]
		});
		close(pipe_fd[OUT]);
		if (fds.prev)
			close(fds.prev);
		_exec_ast(ctx, data, ope->right, (t_fds){
			.in = fds.in,
			.out = pipe_fd[IN],
			.prev = 0
		});
		if (ope->right->type == NODE_LEAF)
			close(pipe_fd[IN]);
	}
}

static void	_exec_ast(t_ctx *ctx, t_exec_data *data, t_ast *ast, t_fds fds)
{
	if (!ast)
		return ;
	if (ast->type == NODE_LEAF)
		_handle_leaf(ctx, data, &ast->leaf, fds);
	else
		_handle_ope(ctx, data, &ast->ope, fds);
}

void	execute_ast(t_ctx *ctx, t_ast *ast)
{
	t_exec_data	data;
	int			status;

	data = make_exec_data(ctx);
	toggle_signal(ctx, S_IGNORE);
	if (ast->type == NODE_LEAF && try_single_builtin(ctx, ast->leaf.redir, \
		(char **)lst_to_array(*ctx->cmd, (t_list *)ast->leaf.func)))
		return ;
	_exec_ast(ctx, &data, ast, (t_fds){0});
	while (data.processes)
	{
		waitpid(data.processes->pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT || WTERMSIG(status) == SIGQUIT)
				write(STDOUT_FILENO, "\n", 1);
			ctx->last_exit_code = 128 + WTERMSIG(status);
			break ;
		}
		else if (WIFEXITED(status))
			ctx->last_exit_code = WEXITSTATUS(status);
		data.processes = data.processes->next;
	}
}
// printf("PID: %data | exit_code: %data\n", data.processes->pid, exit_status);
