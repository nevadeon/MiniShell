/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_allocator.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 16:01:51 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 16:01:55 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLOCK_ALLOCATOR_H
# define BLOCK_ALLOCATOR_H

# include <stdint.h>
# include "allocators/allocator.h"

typedef struct s_block
{
	uint8_t	*mem_start;
	size_t	used_memory;
	size_t	capacity;
}	t_block;

t_alloc	*new_block_allocator(size_t size);
void	*block_alloc_fn(void *data, size_t size);
void	block_free_fn(void *data);

#endif
