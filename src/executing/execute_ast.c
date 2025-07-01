#include "minishell.h"

static t_exec_data	_make_exec_data(t_ctx *c, t_ast *root)
{
	t_exec_data	data;

	data = (t_exec_data){
		.paths = str_split(*c->cmd, env_get_var_value(*c->env, "PATH"), ':'),
		.root = root,
	};
	return (data);
}

void	exec_recursive(t_ctx *ctx, t_exec_data *data, t_ast *ast, t_fds fds)
{
	if (!ast)
		return ;
	if (ast->type == NODE_LEAF)
		handle_leaf(ctx, data, &ast->leaf, fds);
	else
		handle_ope(ctx, data, &ast->ope, fds);
}

void	execute_ast(t_ctx *ctx, t_ast *ast)
{
	t_exec_data	data;
	int			status;

	data = _make_exec_data(ctx, ast);
	toggle_signal(ctx, S_IGNORE);
	if (ast->type == NODE_LEAF && try_single_builtin(ctx, ast->leaf.redir, \
		(char **)lst_to_array(*ctx->cmd, (t_list *)ast->leaf.func)))
		return ;
	exec_recursive(ctx, &data, ast, (t_fds){0});
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
	close_redirections(ast);
}
// printf("PID: %data | exit_code: %data\n", data.processes->pid, exit_status);
