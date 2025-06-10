#include <stdlib.h>
#include "allocator.h"

void	*mem_alloc(t_alloc *allocator, size_t size)
{
	assert(allocator);
	assert(allocator->alloc_fn);
	if (!allocator || !allocator->alloc_fn)
		return (NULL);
	return (allocator->alloc_fn(allocator->data, size));
}

void	free_allocator(t_alloc **ptr_to_allocator)
{
	t_alloc	*allocator;

	allocator = *ptr_to_allocator;
	assert(allocator);
	assert(allocator->free_fn);
	if (!allocator || !allocator->free_fn)
		return ;
	allocator->free_fn(allocator->data);
	allocator->data = NULL;
	free(allocator);
	*ptr_to_allocator = NULL;
}
