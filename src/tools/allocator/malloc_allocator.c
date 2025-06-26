/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_allocator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:45 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "allocators/malloc_allocator.h"

void	*malloc_alloc_fn(void *data, size_t size)
{
	(void)data;
	return (malloc(size));
}

void	malloc_free_fn(void *data)
{
	(void)data;
	return ;
}

t_alloc	*new_malloc_allocator(int unused_param)
{
	t_alloc	*malloc_allocator;

	(void)unused_param;
	malloc_allocator = malloc(sizeof(t_alloc));
	if (!malloc_allocator)
		return (NULL);
	*malloc_allocator = (t_alloc){
		.data = NULL,
		.alloc_fn = malloc_alloc_fn,
		.free_fn = malloc_free_fn,
	};
	return (malloc_allocator);
}
