/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:44:58 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cbuiltins.h"

int	builtin_pwd(t_ctx *unused_ctx, char **unused_args)
{
	char	cwd[PATH_MAX];

	(void)unused_ctx;
	(void)unused_args;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	printf("%s\n", cwd);
	return (0);
}
