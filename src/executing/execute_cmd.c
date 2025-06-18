#include "minishell.h"

static void _exec_failure_print(char **args)
{
	if(errno == EACCES)
	{
		fprintf(stderr, "%s: Permission denied\n", args[CMD_NAME]);
		errno = 126;
	}
	else if (errno == ENOENT)
	{
		fprintf(stderr, "%s: command not found\n", args[CMD_NAME]);
		errno = 127;
	}
	else
		fprintf(stderr, "%s: %s\n", args[CMD_NAME], strerror(errno));
}

void	exec_cmd(t_alloc *alloc, char **env_paths, char **args)
{
	char	*path;
	int		i;

	if (str_chr(args[CMD_NAME], '/'))
		execve(args[CMD_NAME], args, env_get());
	else
	{
		i = -1;
		while (env_paths[++i])
		{
			path = str_vjoin(alloc, 3, env_paths[i], "/", args[CMD_NAME]);
			execve(path, args, env_get());
			if (errno != ENOENT)
				break ;
		}
	}
	_exec_failure_print(args);
}
