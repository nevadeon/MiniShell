#ifndef MGC_ALLOCATOR_H
# define MGC_ALLOCATOR_H

# include "allocators/allocator.h"

typedef struct s_alloc_node
{
	struct s_alloc_node	*next;
	void				*ptr;
}	t_alloc_node;

typedef struct s_malloc_data
{
	t_alloc_node	*head;
}	t_malloc_data;

t_alloc	*new_mgc_allocator(int unused_param);
void	*mgc_alloc_fn(void *data, size_t size);
void	mgc_free_fn(void *data);

#endif
