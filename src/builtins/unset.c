/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:44:59 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cbuiltins.h"

int	builtin_unset(t_ctx *ctx, char **args)
{
	while (*args)
	{
		env_remove_var(ctx, *args);
		args++;
	}
	return (0);
}
