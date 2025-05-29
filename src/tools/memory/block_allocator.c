#include <stdlib.h>
#include "block_allocator.h"

t_fixed_arena	*new_block_data(size_t size)
{
	t_fixed_arena	*arena;

	assert(size > 0);
	arena = malloc(sizeof(t_fixed_arena));
	if (!arena)
		return (NULL);
	*arena = (t_fixed_arena){
		.mem_start = malloc(size),
		.used_memory = 0,
		.capacity = size,
	};
	return (arena);
}

void	*block_alloc_fn(void *data, size_t size)
{
	t_fixed_arena	*arena;
	void			*ptr;

	assert(data);
	assert(size > 0);
	if (size == 0)
		return (NULL);
	arena = (t_fixed_arena *)data;
	assert(arena->mem_start);
	assert((arena->used_memory + size) <= arena->capacity);
	ptr = arena->mem_start + arena->used_memory;
	arena->used_memory += size;
	return (ptr);
}

bool	block_check_fn(void *data)
{
	t_fixed_arena	*arena;

	assert(data);
	arena = (t_fixed_arena *)data;
	if (arena && arena->mem_start)
		return (true);
	return (false);
}

void	block_free_fn(void *data)
{
	t_fixed_arena	*arena;

	if (!data)
		return ;
	arena = (t_fixed_arena *)data;
	free(arena->mem_start);
	arena->mem_start = NULL;
	arena->used_memory = 0;
	arena->capacity = 0;
}

t_allocator	make_block_allocator(size_t size)
{
	t_allocator	fixed_arena_allocator;

	fixed_arena_allocator = (t_allocator){
		.data = new_block_data(size),
		.alloc_fn = block_alloc_fn,
		.check_fn = block_check_fn,
		.free_fn = block_free_fn,
	};
	return (fixed_arena_allocator);
}
