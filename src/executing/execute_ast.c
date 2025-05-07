#include "minishell.h"

static void _execute_ast(t_ast *ast, t_exec_data data);

static void	_handle_ope(t_ast *ast, t_exec_data data)
{
	data.last_ope = ast;
	if (ast->s_ope.type == E_OPE_PIPE)
	{
		data.prev_pipe_fd = data.pipefd[0];
		if (pipe(data.pipefd) == -1)
			exit(666);
		if (ast->s_ope.right->type == E_NODE_CMD)
			data.pipefd[1] = 0;
		_execute_ast(ast->s_ope.right, data);
		_execute_ast(ast->s_ope.left, data);
		close(data.pipefd[0]);
		close(data.pipefd[1]);
	}
}

static void _handle_redirections(t_ast *ast, t_exec_data data)
{
	int				in_fd;
	int				out_fd;
	t_redir_list	*redir;

	//input
	in_fd = data.prev_pipe_fd;
	redir = lst_last(ast->s_cmd.redir_in);
	if (redir)
	{
		if (redir->type == E_REDIR_IN_FILE)
			in_fd = open(redir->content, O_RDONLY);
		else if (redir->type == E_REDIR_IN_HEREDOC)
			in_fd = handle_heredoc(redir->content);
		//quand il y a une redir et un pipe le pipe qui ne sera pas utilise est ferme
		if (data.prev_pipe_fd)
			close(data.prev_pipe_fd);
	}
	if (redir || data.prev_pipe_fd)
		dup_close(in_fd, STDIN_FILENO);

	//output
	out_fd = data.pipefd[1];
	redir = lst_last(ast->s_cmd.redir_out);
	if (redir)
	{
		if (redir->type == E_REDIR_OUT_TRUNCATE)
			out_fd = open(redir->content, O_CREAT | O_TRUNC);
		else if (redir->type == E_REDIR_OUT_APPEND)
			out_fd = open(redir->content, O_CREAT | O_APPEND);
		//quand il y a une redir et un pipe le pipe qui ne sera pas utilise est ferme
		if (data.pipefd[1])
			close(data.pipefd[1]);
	}
	if (redir || data.pipefd[1])
		dup_close(out_fd, STDOUT_FILENO);

	//closing unused end of the pipe if there is a pipe
	if (data.pipefd[1])
		close(data.pipefd[0]);
}

static void	_handle_leaf(t_ast *ast, t_exec_data data)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		_handle_redirections(ast, data);
		exec_cmd(data.env_paths, ast->s_cmd.args);
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
	if (ast->type == E_NODE_CMD)
		_handle_leaf(ast, data);
	else
		_handle_ope(ast, data);
}

t_exec_data	init_exec_data(t_ast *ast)
{
	t_exec_data	data;

	data.root = ast;
	data.last_ope = NULL;
	data.pid_list = NULL;
	data.prev_pipe_fd = 0;
	data.pipefd[0] = 0;
	data.pipefd[1] = 0;
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
