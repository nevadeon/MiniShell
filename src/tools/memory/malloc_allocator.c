#include <stdlib.h>
#include "malloc_allocator.h"

void	*malloc_alloc_fn(void *data, size_t size)
{
	(void)data;
	return (malloc(size));
}

t_allocator	make_malloc_allocator(void)
{
	t_allocator	malloc_allocator;

	malloc_allocator = (t_allocator){
		.data = NULL,
		.alloc_fn = malloc_alloc_fn,
		.check_fn = NULL,
		.free_fn = NULL,
	};
	return (malloc_allocator);
}
