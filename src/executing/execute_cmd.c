#include "minishell.h"

void	exec_cmd(t_alloc *cmd, char **env_paths, t_str_list *arg_list)
{
	char	**args;
	char	*path;
	int		i;

	args = (char **) lst_to_array(cmd, (t_list *)arg_list);
	if (str_chr(args[CMD_NAME], '/'))
		execve(args[CMD_NAME], args, env_get());
	else
	{
		i = -1;
		while (env_paths[++i])
		{
			path = str_vjoin(cmd, 3, env_paths[i], "/", args[CMD_NAME]);
			execve(path, args, env_get());
		}
	}
	fprintf(stderr, "%s: %s\n", args[CMD_NAME], strerror(errno));
}
