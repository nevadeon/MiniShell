#include "minishell.h"

static void	_execute_ast_recursive(t_ast *ast, t_exec_data *data);

t_exec_data	make_exec_data(t_alloc **a_prog, t_alloc **a_cmd, t_ast *ast)
{
	t_exec_data	data;

	data = (t_exec_data){
		.alloc_cmd = a_cmd,
		.alloc_prog = a_prog,
		.root = ast,
		.last_ope = NULL,
		.prev_pipe_fd = 0,
		.pipefd = {0, 0},
		.env_paths = str_split(*a_cmd, env_get_var_value(*a_cmd, "PATH"), ':'),
	};
	return (data);
}

static void	_handle_leaf(t_ast *ast, t_exec_data *data)
{
	pid_t	pid;
	int 	in_fd;
	int		out_fd;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		in_fd = handle_input_redir(ast->s_leaf.redir_in, data->prev_pipe_fd);
		out_fd = handle_output_redir(ast->s_leaf.redir_out, data->pipefd[1]);
		exec_cmd(*(data->alloc_cmd), data->env_paths, ast->s_leaf.func);
		close(in_fd);
		close(out_fd);
		free_allocator(data->alloc_cmd);
		free_allocator(data->alloc_prog);
		exit(errno);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

static void	_handle_ope(t_ast *ast, t_exec_data *data)
{
	int	temp_fd;
	int	temp2_fd;

	data->last_ope = ast;
	if (ast->s_ope.type == E_OPE_PIPE)
	{
		data->prev_pipe_fd = data->pipefd[0];
		if (pipe(data->pipefd) == -1)
		{
			perror("pipe");
			exit(666);
		}
		temp_fd = data->pipefd[1];
		temp2_fd = data->prev_pipe_fd;
		if (ast->s_ope.right->type == E_NODE_LEAF)
		{
			data->pipefd[1] = 0;
			data->prev_pipe_fd = data->pipefd[0];
		}
		_execute_ast_recursive(ast->s_ope.right, data);
		data->pipefd[1] = temp_fd;
		data->prev_pipe_fd = temp2_fd;
		_execute_ast_recursive(ast->s_ope.left, data);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
	}
}

static void	_execute_ast_recursive(t_ast *ast, t_exec_data *data)
{
	if (!ast)
		return ;
	if (ast->type == E_NODE_LEAF)
		_handle_leaf(ast, data);
	else
		_handle_ope(ast, data);
}

void	execute_ast(t_alloc **alloc_prog, t_alloc **alloc_cmd, t_ast *ast)
{
	t_exec_data	data;

	data = make_exec_data(alloc_prog, alloc_cmd, ast);
	_execute_ast_recursive(ast, &data);
}
