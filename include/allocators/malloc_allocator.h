/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_allocator.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:51 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 16:01:55 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_ALLOCATOR_H
# define MALLOC_ALLOCATOR_H

# include "allocators/allocator.h"

t_alloc	*new_malloc_allocator(int unused_param);
void	*malloc_alloc_fn(void *data, size_t size);
void	malloc_free_fn(void *data);

#endif
