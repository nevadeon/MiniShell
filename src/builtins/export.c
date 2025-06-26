/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:44:57 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cbuiltins.h"
#include "stdlib.h"

static const char	*g_assets[] = {
	"assets/segfault.ascii",
	"assets/willem_dafoe.ascii",
	"assets/absolute_cinema.ascii",
	"assets/got_them.ascii",
	"assets/monkashh.ascii",
	"assets/well.ascii",
	"assets/calamardo.ascii",
	"assets/moai_statue.ascii",
};

static const int	g_assets_size = sizeof(g_assets) / sizeof(g_assets[0]);

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
	static int	i = 0;

	print_file(g_assets[i++]);
	if (i >= g_assets_size)
		i = 1;
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
	ctx->last_exit_code = 0;
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
	return (ctx->last_exit_code);
}
