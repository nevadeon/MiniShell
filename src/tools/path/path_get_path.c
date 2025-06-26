/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_get_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:51 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/path.h"

char	*path_get_path(t_alloc *alloc, char *filepath)
{
	size_t	index;
	size_t	last_slash_index;
	char	*path_cpy;

	if (!filepath)
		return (str_dup(alloc, ""));
	last_slash_index = 0;
	index = 0;
	path_cpy = str_dup(alloc, filepath);
	if (!path_cpy)
		return (NULL);
	while (path_cpy[index])
	{
		if (path_cpy[index] == '/')
			last_slash_index = index;
		index++;
	}
	if (last_slash_index == 0)
		return (str_dup(alloc, ""));
	path_cpy[last_slash_index + 1] = '\0';
	return (path_cpy);
}
