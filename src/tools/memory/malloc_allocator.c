#include <stdlib.h>
#include "malloc_allocator.h"

void	*malloc_alloc_fn(void *data, size_t size)
{
	(void)data;
	return (malloc(size));
}

t_alloc	make_malloc_allocator(void)
{
	t_alloc	malloc_allocator;

	malloc_allocator = (t_alloc){
		.data = NULL,
		.alloc_fn = malloc_alloc_fn,
		.free_fn = NULL,
	};
	return (malloc_allocator);
}
