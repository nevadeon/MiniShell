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

bool	block_check_fn(void *data)
{
	t_block	*block;

	assert(data);
	block = (t_block *)data;
	return (block && block->mem_start);
}

void	block_free_fn(void *data)
{
	t_block	*block;

	assert(data);
	if (!data)
		return ;
	block = (t_block *)data;
	free(block->mem_start);
	block->mem_start = NULL;
	block->used_memory = 0;
	block->capacity = 0;
}

t_allocator	make_block_allocator(size_t size)
{
	t_allocator	block_allocator;

	assert(size > 0);
	block_allocator = (t_allocator){
		.data = _new_block_data(size),
		.alloc_fn = block_alloc_fn,
		.check_fn = block_check_fn,
		.free_fn = block_free_fn,
	};
	return (block_allocator);
}
