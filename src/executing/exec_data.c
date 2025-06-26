/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:03 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec_data	make_exec_data(t_ctx *c)
{
	t_exec_data	data;

	data = (t_exec_data){
		.c = c,
		.to_close = 0,
		.paths = str_split(*c->cmd, env_get_var_value(*c->env, "PATH"), ':'),
	};
	return (data);
}
