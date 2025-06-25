#ifndef ARENA_ALLOCATOR_H
# define ARENA_ALLOCATOR_H

# include <stdint.h>
# include "allocators/allocator.h"

typedef struct s_block_list
{
	struct s_block_list	*next;
	uint8_t				*mem_start;
}	t_block_list;

typedef struct s_arena
{
	t_block_list	*blocks;
	size_t			used_memory;
	size_t			capacity;
}	t_arena;

t_alloc	*new_arena_allocator(size_t size);
void	*arena_alloc_fn(void *data, size_t size);
void	arena_free_fn(void *data);

#endif
