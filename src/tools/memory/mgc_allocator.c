#include <stdlib.h>
#include "allocators/mgc_allocator.h"

void	*mgc_alloc_fn(void *data, size_t size)
{
	t_malloc_data	*alloc_data;
	t_alloc_node	*new_node;
	void			*ptr;

	alloc_data = (t_malloc_data *)data;
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_alloc_node));
	if (!new_node)
		return (free(ptr), NULL);
	*new_node = (t_alloc_node){
		.next = alloc_data->head,
		.ptr = ptr,
	};
	alloc_data->head = new_node;
	return (ptr);
}

void	mgc_free_fn(void *data)
{
	t_malloc_data	*alloc_data;
	t_alloc_node	*current;
	t_alloc_node	*next;

	alloc_data = (t_malloc_data *)data;
	current = alloc_data->head;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	free(alloc_data);
}

t_alloc	*new_mgc_allocator(int unused_param)
{
	t_alloc			*malloc_allocator;
	t_malloc_data	*data;

	(void)unused_param;
	malloc_allocator = malloc(sizeof(t_alloc));
	if (!malloc_allocator)
		return (NULL);
	data = malloc(sizeof(t_malloc_data));
	if (!data)
		return (free(malloc_allocator), NULL);
	data->head = NULL;
	*malloc_allocator = (t_alloc){
		.data = data,
		.alloc_fn = mgc_alloc_fn,
		.free_fn = mgc_free_fn,
	};
	return (malloc_allocator);
}
