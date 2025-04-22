#include "minishell.h"

void	exec_cmd(char **env_paths, t_str_list *arg_list)
{
	char **args;
	char *cmd_name;
	char *path;
	int	i;

	args = (char **) lst_to_array(E_LFT_FUNC, (t_list *)arg_list);
	cmd_name = args[CMD_NAME_INDEX];
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
