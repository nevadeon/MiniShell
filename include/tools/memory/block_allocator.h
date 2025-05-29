#ifndef FIXED_ARENA_H
# define FIXED_ARENA_H

# include <stddef.h>
# include <stdbool.h>
# include <assert.h>
# include <stdint.h>
# include "allocator.h"

typedef struct s_fixed_arena
{
	uint8_t	*mem_start;
	size_t	used_memory;
	size_t	capacity;
}	t_fixed_arena;

t_allocator		make_block_allocator(size_t size);
t_fixed_arena	*new_block_data(size_t size);
void			*block_alloc_fn(void *data, size_t size);
bool			block_check_fn(void *data);
void			block_free_fn(void *data);

#endif
