#include "allocator.h"

static void	assert_allocator(t_allocator *allocator)
{
	assert(allocator);
	assert(allocator->data);
	assert(allocator->alloc_fn);
	assert(allocator->check_fn);
	assert(allocator->free_fn);
}

void	*mem_alloc(t_allocator *allocator, size_t size)
{
	assert_allocator(allocator);
	return (allocator->alloc_fn(allocator->data, size));
}

bool	check_allocator(t_allocator *allocator)
{
	assert_allocator(allocator);
	return (allocator->check_fn(allocator->data));
}

void	free_allocator(t_allocator *allocator)
{
	assert_allocator(allocator);
	allocator->free_fn(allocator->data);
	allocator->data = NULL;
	allocator->alloc_fn = NULL;
	allocator->check_fn = NULL;
	allocator->free_fn = NULL;
}
