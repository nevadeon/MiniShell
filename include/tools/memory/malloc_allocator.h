#ifndef MALLOC_ALLOCATOR_H
# define MALLOC_ALLOCATOR_H

#include "allocator.h"

t_allocator	make_malloc_allocator();
void		*malloc_alloc_fn(void *data, size_t size);

#endif
