#include "allocator.h"

void	*mem_alloc(t_allocator *allocator, size_t size)
{
	assert(allocator);
	assert(allocator->alloc_fn);
	return (allocator->alloc_fn(allocator->data, size));
}

bool	check_allocator(t_allocator *allocator)
{
	assert(allocator);
	assert(allocator->check_fn);
	if (allocator->check_fn(allocator->data)
		&& allocator->alloc_fn
		&& allocator->check_fn
		&& allocator->free_fn)
		return (true);
	return (false);
}

void	free_allocator(t_allocator *allocator)
{
	assert(allocator);
	assert(allocator->free_fn);
	allocator->free_fn(allocator->data);
	allocator->data = NULL;
	allocator->alloc_fn = NULL;
	allocator->check_fn = NULL;
	allocator->free_fn = NULL;
}
