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

t_allocator		make_fixed_arena_allocator(size_t size);
t_fixed_arena	*new_fixed_arena_data(size_t size);
void			*fixed_arena_alloc_fn(void *data, size_t size);
bool			fixed_arena_check_fn(void *data);
void			fixed_arena_free_fn(void *data);

#endif
