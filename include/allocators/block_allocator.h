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
