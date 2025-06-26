/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_get_filename.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:50 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools/path.h"
#include "stdio.h"

char	*path_get_filename(t_alloc *alloc, char *filepath)
{
	char	*pattern;

	pattern = str_rchr(filepath, '/');
	if (str_equals(pattern, filepath))
		return (filepath);
	pattern = str_dup(alloc, pattern + 1);
	return (pattern);
}
