#include <stdlib.h>
#include "block_allocator.h"

static t_block	*_new_block_data(size_t size)
{
	t_block	*block;

	block = malloc(sizeof(t_block));
	if (!block)
		return (NULL);
	*block = (t_block){
		.mem_start = malloc(size),
		.used_memory = 0,
		.capacity = size,
	};
	if (!block->mem_start)
		return (free(block), NULL);
	return (block);
}

void	*block_alloc_fn(void *data, size_t size)
{
	t_block	*block;
	void	*ptr;

	assert(size > 0);
	assert(data);
	block = (t_block *)data;
	assert(block->mem_start);
	assert((block->used_memory + size) <= block->capacity);
	ptr = block->mem_start + block->used_memory;
	block->used_memory += size;
	return (ptr);
}

void	block_free_fn(void *data)
{
	t_block	*block;

	block = (t_block *)data;
	assert(block->mem_start);
	free(block->mem_start);
	*block = (t_block){0};
}

t_alloc	*new_block_allocator(size_t size)
{
	t_alloc	*block_allocator;

	assert(size > 0);
	block_allocator = malloc(sizeof(t_alloc));
	if (!block_allocator)
		return (NULL);
	*block_allocator = (t_alloc){
		.data = _new_block_data(size),
		.alloc_fn = block_alloc_fn,
		.free_fn = block_free_fn,
	};
	if (!block_allocator->data)
		return (free(block_allocator), NULL);
	return (block_allocator);
}
