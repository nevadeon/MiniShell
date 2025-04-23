#include "minishell.h"

static void _execute_ast(t_ast *ast, t_exec_data data);

static void	_execute_ope(t_ast *ast, t_exec_data data)
{
	data.last_ope = ast;
	if (ast->s_ope.type == E_OPE_PIPE)
	{
		data.prev_pipe_fd = data.pipefd[0];
		if (pipe(data.pipefd) == -1)
			exit(666);
		_execute_ast(ast->s_ope.right, data);
		_execute_ast(ast->s_ope.left, data);
		close(data.pipefd[0]);
		close(data.pipefd[1]);
	}
}

static void	_execute_leaf(t_ast *ast, t_exec_data data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (ast != data.root)
		{
			if (ast == data.last_ope->s_ope.right)
			{
				dup_close(data.pipefd[0], STDIN_FILENO);
				close(data.pipefd[1]);
			}
			else if (data.last_ope == data.root)
			{
				dup_close(data.pipefd[1], STDOUT_FILENO);
				close(data.pipefd[0]);
			}
			else
			{
				dup_close(data.prev_pipe_fd, STDIN_FILENO);
				dup_close(data.pipefd[1], STDOUT_FILENO);
				close(data.pipefd[0]);
			}
		}
		exec_cmd(data.env_paths, ast->s_leaf.s_func.args);
		exit(666);
	}
	else
	{
		lst_add_front((t_list **)&data.pid_list, (t_list *)lst_pid_new(pid));
	}
}

static void	_execute_ast(t_ast *ast, t_exec_data data)
{
	if (!ast)
		return ;
	if (ast->type == E_NODE_LEAF)
		_execute_leaf(ast, data);
	else
		_execute_ope(ast, data);
}

t_exec_data	init_exec_data(t_ast *ast)
{
	t_exec_data	data;

	data.root = ast;
	data.last_ope = NULL;
	data.pid_list = NULL;
	data.prev_pipe_fd = -1;
	data.pipefd[0] = -1;
	data.pipefd[1] = -1;
	data.env_paths = str_split(E_LFT_TASK, env_get_var_value("PATH"), ':');
	return (data);
}

void	execute_ast(t_ast *ast)
{
	t_exec_data	data;
	int			status;

	data = init_exec_data(ast);
	_execute_ast(ast, data);
	while (data.pid_list)
	{
		waitpid(data.pid_list->pid, &status, 0);
		data.pid_list = data.pid_list->next;
	}
}
