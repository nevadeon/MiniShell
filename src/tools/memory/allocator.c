#include <stdlib.h>
#include "allocator.h"

void	*mem_alloc(t_alloc *allocator, size_t size)
{
	assert(allocator);
	assert(allocator->alloc_fn);
	return (allocator->alloc_fn(allocator->data, size));
}

void	free_allocator(t_alloc **ptr_to_allocator)
{
	t_alloc	*allocator;

	allocator = *ptr_to_allocator;
	assert(allocator);
	if (!allocator)
		return ;
	assert(allocator->free_fn);
	assert(allocator->data);
	allocator->free_fn(allocator->data);
	allocator->data = NULL;
	free(allocator);
	*ptr_to_allocator = NULL;
}
