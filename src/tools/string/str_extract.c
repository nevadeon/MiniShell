/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_extract.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:46:01 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocators/allocator.h"
#include "tools/str.h"

char	*str_extract(t_alloc *alloc, char *s, size_t start, size_t end)
{
	char	*ret;
	size_t	len;

	len = end - start;
	ret = mem_alloc(alloc, len + 1);
	ret = str_memcpy(ret, s + start, len);
	ret[len] = '\0';
	return (ret);
}
