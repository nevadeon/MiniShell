#include "cbuiltins.h"
#include "stdlib.h"

void	print_file(t_alloc *a, const char *path)
{
	char	*str;
	int		fd;

	fd = open(path, O_RDONLY);
	while (1)
	{
		str = str_gnl(a, fd);
		if (!str)
			break ;
		printf("%s", str);
	}
	close(fd);
}

static bool	_is_var_name_valid(char *str)
{
	size_t	index;

	index = 0;
	if ((str)[index] != '_' && !char_isalpha((str)[index]))
		return (false);
	while (char_isalnum((str)[index]) || (str)[index] == '_')
		index++;
	return (str[index] == '=');
}

int	builtin_export(t_ctx *ctx, char **args)
{
	if (!args[1])
		return (print_file(*ctx->cmd, "assets/skill_issue.ascii"), 0);
	(void)ctx;
	args++;
	while (*args)
	{
		if (_is_var_name_valid(*args))
			env_set_var_value(ctx, *args);
		else
		{
			io_dprintf(STDERR, "bash: export: `%s': not a valid ", *args);
			io_dprintf(STDERR, "identifier\n");
			ctx->last_exit_code = ERR_UNKNOWN;
			ctx->last_exit_code = 1;
		}
		args++;
	}
	return (0);
}
