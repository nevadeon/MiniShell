#ifndef ALLOCATOR_H
# define ALLOCATOR_H

# include <stddef.h>
# include <stdbool.h>
# include <assert.h>

typedef void	*(*t_alloc_fn)(void *data, size_t size);
typedef bool	(*t_check_fn)(void *data);
typedef void	(*t_free_fn)(void *data);

typedef struct s_allocator
{
	void		*data;
	t_alloc_fn	alloc_fn;
	t_free_fn	free_fn;
	t_check_fn	check_fn;
}	t_allocator;

void	*mem_alloc(t_allocator *allocator, size_t size);
void	free_allocator(t_allocator *allocator);
bool	check_allocator(t_allocator *allocator);

#endif
