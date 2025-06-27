#include "minishell.h"

static void	_exec_ast(t_exec_data *d, t_ast *ast, int fd1, int fd2);

static void	_clean_exit(t_exec_data *d, int final_in, int final_out)
{
	int	exit_status;

	if (final_in)
		close(final_in);
	if (final_out)
		close(final_out);
	exit_status = d->c->last_exit_code;
	free_allocator(d->c->cmd);
	free_allocator(d->c->prog);
	exit(exit_status);
}

static void	_handle_leaf(t_exec_data *d, t_ast *a, int pipe_out, int pipe_in)
{
	pid_t	pid;
	int		final_in;
	int		final_out;

	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	if (pid == 0)
	{
		toggle_signal(d->c, S_CHILD);
		final_in = handle_input_redir(a->s_leaf.redir_in, pipe_out);
		final_out = handle_output_redir(a->s_leaf.redir_out, pipe_in);
		if (d->to_close)
			close(d->to_close);
		exec_cmd(d->c, d->paths, \
			(char **)lst_to_array(*(d->c->cmd), (t_list *)a->s_leaf.func));
		_clean_exit(d, final_in, final_out);
	}
	else
	{
		lst_add_front((t_list **) &d->processes,
			(t_list *) lst_pid_new(*d->c->cmd, pid));
	}
}

static void	_handle_ope(t_exec_data *d, t_ast *a, int std_in, int prev_in)
{
	int	pipe_fd[2];

	if (a->s_ope.type == E_OPE_PIPE)
	{
		if (pipe(pipe_fd) == -1)
			return (perror("pipe"));
		d->to_close = pipe_fd[PIPE_IN];
		_exec_ast(d, a->s_ope.left, pipe_fd[PIPE_OUT], prev_in);
		close(pipe_fd[PIPE_OUT]);
		if (prev_in)
			close(prev_in);
		d->to_close = 0;
		_exec_ast(d, a->s_ope.right, std_in, pipe_fd[PIPE_IN]);
		if (a->s_ope.right->type == E_WORD)
			close(pipe_fd[PIPE_IN]);
	}
}

static void	_exec_ast(t_exec_data *d, t_ast *ast, int fd1, int fd2)
{
	if (!ast)
		return ;
	if (ast->type == E_WORD)
		_handle_leaf(d, ast, fd1, fd2);
	else
		_handle_ope(d, ast, fd1, fd2);
}

void	execute_ast(t_ctx *ctx, t_ast *ast)
{
	t_exec_data	data;
	int			status;
	int			exit_status;

	data = make_exec_data(ctx);
	toggle_signal(ctx, S_IGNORE);
	if (ast->type == E_WORD
		&& try_single_builtin(ctx, ast))
		return ;
	_exec_ast(&data, ast, 0, 0);
	while (data.processes)
	{
		waitpid(data.processes->pid, &status, 0);
		exit_status = WEXITSTATUS(status);
		ctx->last_exit_code = exit_status;
		data.processes = data.processes->next;
	}
}
// printf("PID: %d | exit_status: %d\n", data.processes->pid, exit_status);
