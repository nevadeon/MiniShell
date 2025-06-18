#include "minishell.h"

static void	_exec_ast(t_ast *ast, t_exec_data *data, int fd1, int fd2);

t_exec_data	make_exec_data(t_alloc **a_prog, t_alloc **a_cmd)
{
	t_exec_data	data;

	data = (t_exec_data){
		.alloc_cmd = a_cmd,
		.alloc_prog = a_prog,
		.to_close = 0,
		.env_paths = str_split(*a_cmd, env_get_var_value(*a_cmd, "PATH"), ':'),
	};
	return (data);
}

static void _error(const char *str)
{
	perror(str);
}

static void _handle_exec_failure(t_exec_data *d, int final_in, int final_out)
{
	if (final_in)
		close(final_in);
	if (final_out)
		close(final_out);
	free_allocator(d->alloc_cmd);
	free_allocator(d->alloc_prog);
	exit(errno);
}

static void	_handle_leaf(t_ast *a, t_exec_data *d, int pipe_out, int pipe_in)
{
	pid_t	pid;
	int 	final_in;
	int		final_out;

	pid = fork();
	if (pid == -1)
		return (_error("fork"));
	if (pid == 0)
	{
		final_in = handle_input_redir(a->s_leaf.redir_in, pipe_out);
		final_out = handle_output_redir(a->s_leaf.redir_out, pipe_in);
		if (d->to_close)
			close(d->to_close);
		exec_cmd(*(d->alloc_cmd), d->env_paths, \
			(char **)lst_to_array(*(d->alloc_cmd), (t_list *)a->s_leaf.func));
		_handle_exec_failure(d, final_in, final_out);
	}
	else
		lst_add_front((t_list **) &d->processes,
			(t_list *) lst_pid_new(*d->alloc_cmd, pid));
}

static void	_handle_ope(t_ast *a, t_exec_data *d, int std_in, int prev_in)
{
	int	pipe_fd[2];

	if (a->s_ope.type == E_OPE_PIPE)
	{
		if (pipe(pipe_fd) == -1)
			return (_error("pipe"));
		d->to_close = pipe_fd[PIPE_IN];
		_exec_ast(a->s_ope.left, d, pipe_fd[PIPE_OUT], prev_in);
		close(pipe_fd[PIPE_OUT]);
		if (prev_in)
			close(prev_in);
		d->to_close = 0;
		_exec_ast(a->s_ope.right, d, std_in, pipe_fd[PIPE_IN]);
		if (a->s_ope.right->type == E_NODE_LEAF)
			close(pipe_fd[PIPE_IN]);
	}
}

static void	_exec_ast(t_ast *ast, t_exec_data *data, int fd1, int fd2)
{
	if (!ast)
		return ;
	if (ast->type == E_NODE_LEAF)
		_handle_leaf(ast, data, fd1, fd2);
	else
		_handle_ope(ast, data, fd1, fd2);
}

void	execute_ast(t_alloc **alloc_prog, t_alloc **alloc_cmd, t_ast *ast)
{
	t_exec_data	data;
	int			status;
	int			exit_status;

	data = make_exec_data(alloc_prog, alloc_cmd);
	_exec_ast(ast, &data, 0, 0);
	while (data.processes)
	{
		waitpid(data.processes->pid, &status, 0);
		exit_status = WEXITSTATUS(status);
		printf("PID: %d | exit_status: %d\n", data.processes->pid, exit_status);
		data.processes = data.processes->next;
	}
}
