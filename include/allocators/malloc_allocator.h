#ifndef MALLOC_ALLOCATOR_H
# define MALLOC_ALLOCATOR_H

# include "allocators/allocator.h"

t_alloc	*new_malloc_allocator(int unused_param);
void	*malloc_alloc_fn(void *data, size_t size);
void	malloc_free_fn(void *data);

#endif
