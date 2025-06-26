/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:44:55 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cbuiltins.h"
#include "allocators/allocator.h"

static int	_print_error(t_ctx *ctx, const char *msg)
{
	io_dprintf(STDERR, "bash: env: %s\n", msg);
	ctx->last_exit_code = 1;
	return (1);
}

int	builtin_env(t_ctx *ctx, char **unused_args)
{
	char	**env;
	int		i;

	if (unused_args[1])
		return (_print_error(ctx, "too many arguments"));
	(void)unused_args;
	env = *ctx->env;
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	return (0);
}
