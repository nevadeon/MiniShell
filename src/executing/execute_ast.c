#include "minishell.h"

static int _execute_ast(t_ast *ast, char **env_paths)
{
	if (!ast)
		return 0;
	if (ast->type == E_NODE_LEAF)
		return (_execute_leaf_node());
	if (ast->type == E_NODE_OPE)
		return (_execute_operator_node());
	return (666);
}

static void	_wait_childrens(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == E_NODE_LEAF)
	{
		if (ast->s_leaf.type == E_LEAF_FUNC)
			wait(0);
	}
	else if (ast->type == E_NODE_OPE)
	{
		_wait_childrens(ast->s_ope.left);
		_wait_childrens(ast->s_ope.right);
	}
}

void	execute_ast(t_ast *ast)
{
	char **env_paths = str_split(E_LFT_TASK, env_get_var_value("PATH"), ':');

	_execute_ast(ast, env_paths);
	_wait_childrens(ast);
}
