/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_on_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:52:27 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/30 11:52:28 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_on_path(t_ctx *ctx, char *path, char **args, int not_found_err)
{
	struct stat	sb;

	if (stat(path, &sb) == 0)
	{
		if (S_ISDIR(sb.st_mode))
			return (throw_error(ctx, E_IS_DIR, args[CMD_NAME]));
		execve(path, args, *ctx->env);
		if (errno == EACCES)
			return (throw_error(ctx, E_PERM_DENIED, args[CMD_NAME]));
		if (errno == ENOEXEC)
			return (throw_error(ctx, E_NOT_EXECUTABLE, args[CMD_NAME]));
		if (errno != ENOENT)
			return (throw_error(ctx, E_USE_ERRNO, args[CMD_NAME]));
	}
	if (not_found_err)
		throw_error(ctx, not_found_err, args[CMD_NAME]);
}
