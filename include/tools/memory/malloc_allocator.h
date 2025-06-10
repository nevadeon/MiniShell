#ifndef MALLOC_ALLOCATOR_H
# define MALLOC_ALLOCATOR_H

# include "allocator.h"

t_alloc	*new_malloc_allocator(void);
void	*malloc_alloc_fn(void *data, size_t size);

#endif
