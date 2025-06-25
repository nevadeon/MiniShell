#ifndef ALLOCATOR_H
# define ALLOCATOR_H

# include <stddef.h>
# include <assert.h>

typedef void	*(*t_alloc_fn)(void *data, size_t size);
typedef void	(*t_free_fn)(void *data);

typedef struct s_allocator
{
	void		*data;
	t_alloc_fn	alloc_fn;
	t_free_fn	free_fn;
}	t_alloc;

void	*mem_alloc(t_alloc *allocator, size_t size);
void	free_allocator(t_alloc **allocator);

#endif
