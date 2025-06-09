#include "minishell.h"

static void	_execute_ast_recursive(t_ast *ast, t_exec_data *data);

t_exec_data	make_exec_data(t_allocator *prog, t_allocator *cmd, t_ast *ast)
{
	t_exec_data	data;

	data = (t_exec_data){
		.cmd = cmd,
		.prog = prog,
		.root = ast,
		.last_ope = NULL,
		.pid_list = NULL,
		.prev_pipe_fd = 0,
		.pipefd = {0, 0},
		.env_paths = str_split(cmd, env_get_var_value(cmd, "PATH"), ':'),
	};
	return (data);
}

static void	_handle_leaf(t_ast *ast, t_exec_data *data)
{
	pid_t	pid;
	int 	in_fd;
	int		out_fd;

	pid = fork();
	if (pid == 0)
	{
		in_fd = handle_input_redir(ast->s_leaf.redir_in, data->prev_pipe_fd);
		out_fd = handle_output_redir(ast->s_leaf.redir_out, data->pipefd[1]);
		exec_cmd(data->cmd, data->env_paths, ast->s_leaf.func);
		close(in_fd);
		close(out_fd);
		free_allocator(data->cmd);
		free_allocator(data->prog);
		exit(errno);
	}
	else
	{
		lst_add_front((t_list **)&data->pid_list, \
			(t_list *)lst_pid_new(data->cmd, pid));
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

void	execute_ast(t_allocator *prog, t_allocator *cmd, t_ast *ast)
{
	t_exec_data	data;
	int			status;

	data = make_exec_data(prog, cmd, ast);
	_execute_ast_recursive(ast, &data);
	while (data.pid_list)
	{
		waitpid(data.pid_list->pid, &status, 0);
		data.pid_list = data.pid_list->next;
	}
}
