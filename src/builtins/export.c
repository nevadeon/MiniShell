#include "cbuiltins.h"
#include "stdlib.h"

void	print_file(const char *path)
{
	t_alloc	*cmd;
	char	*str;
	int		fd;

	cmd = new_mgc_allocator(0);
	fd = open(path, O_RDONLY);
	while (1)
	{
		str = str_gnl(cmd, fd);
		if (!str)
			break ;
		printf("%s", str);
	}
	close(fd);
	free_allocator(&cmd);
}

void	skill_issue(void)
{
	static int	i = 1;

	if (i == 7)
		i = 2;
	if (i == 1)
		print_file("assets/segfault.ascii");
	else if (i == 2)
		print_file("assets/willem_dafoe.ascii");
	else if (i == 3)
		print_file("assets/absolute_cinema.ascii");
	else if (i == 4)
		print_file("assets/well.ascii");
	else if (i == 5)
		print_file("assets/monkashh.ascii");
	else if (i == 6)
		print_file("assets/calamardo.ascii");
	i++;
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
		return (skill_issue(), 0);
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
			ctx->last_exit_code = E_UNKNOWN;
			ctx->last_exit_code = 1;
		}
		args++;
	}
	return (0);
}
