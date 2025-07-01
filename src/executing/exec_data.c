#include "minishell.h"

t_exec_data	make_exec_data(t_ctx *c)
{
	t_exec_data	data;

	data = (t_exec_data){
		.paths = str_split(*c->cmd, env_get_var_value(*c->env, "PATH"), ':'),
	};
	return (data);
}
