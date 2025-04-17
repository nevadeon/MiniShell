#include "minishell.h"

void	exec_cmd(char **env_paths, char *cmd_name, t_args *arg_list)
{
	int	i;
	char *path;
	char **args;

	args = (char **) lst_to_tab(E_LFT_FUNC, arg_list);
	if (str_chr(cmd_name, '/'))
		execve(cmd_name, args, env_get());
	else
	{
		i = -1;
		while (env_paths[++i])
		{
			path = str_vjoin(E_LFT_FUNC, 3, env_paths[i], "/", cmd_name);
			execve(path, args, env_get());
		}
	}
	mem_free_instance(E_LFT_FUNC);
}
