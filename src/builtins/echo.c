/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:44:54 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cbuiltins.h"

int	builtin_echo(t_ctx *unused_ctx, char **args)
{
	bool	newline;
	int		i;

	(void)unused_ctx;
	if (!args[1])
		return (printf("\n"), 0);
	newline = (str_cmp(args[1], "-n") != 0);
	i = !newline + 1;
	printf("%s", args[i]);
	while (args[++i])
		printf(" %s", args[i]);
	if (newline)
		printf("\n");
	return (0);
}
