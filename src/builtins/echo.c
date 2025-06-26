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

static bool	_is_option(const char *str, char c)
{
	int	i;

	if (str[0] != '-')
		return (false);
	i = 1;
	while (str[i])
	{
		if (str[i] != c)
			return (false);
		i++;
	}
	return (true);
}

int	builtin_echo(t_ctx *unused_ctx, char **args)
{
	bool	newline;
	int		i;

	(void)unused_ctx;
	newline = true;
	i = 1;
	while (args[i] && _is_option(args[i], 'n'))
	{
		newline = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
