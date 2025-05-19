#include <stdlib.h>
#include "fixed_arena.h"

t_fixed_arena	*new_fixed_arena_data(size_t size)
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

void	*fixed_arena_alloc_fn(void *data, size_t size)
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

bool	fixed_arena_check_fn(void *data)
{
	t_fixed_arena	*arena;

	assert(data);
	arena = (t_fixed_arena *)data;
	if (arena && arena->mem_start)
		return (true);
	return (false);
}

void	fixed_arena_free_fn(void *data)
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

t_allocator	make_fixed_arena_allocator(size_t size)
{
	t_allocator	fixed_arena_allocator;

	fixed_arena_allocator = (t_allocator){
		.data = new_fixed_arena_data(size),
		.alloc_fn = fixed_arena_alloc_fn,
		.check_fn = fixed_arena_check_fn,
		.free_fn = fixed_arena_free_fn,
	};
	return (fixed_arena_allocator);
}
