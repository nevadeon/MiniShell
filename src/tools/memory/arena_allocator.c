#include <stdlib.h>
#include "arena_allocator.h"

static void	_list_add_front(t_block_list **list, t_block_list *new_node)
{
	if (*list)
		new_node->next = *list;
	*list = new_node;
}

static t_block_list	*_new_block(size_t size)
{
	void			*new_block;
	t_block_list	*new_node;

	new_block = malloc(size);
	if (!new_block)
		return (NULL);
	new_node = malloc(sizeof(t_block_list));
	if (!new_node)
		return (free(new_block), NULL);
	new_node->mem_start = new_block;
	new_node->next = NULL;
	return (new_node);
}

static t_arena	*_new_arena_data(size_t size)
{
	t_arena	*arena;

	arena = malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	*arena = (t_arena){
		.blocks = _new_block(size),
		.capacity = size,
		.used_memory = 0,
	};
	if (!arena->blocks)
		return (free(arena), NULL);
	return (arena);
}

void	*arena_alloc_fn(void *data, size_t size)
{
	t_arena			*a;
	t_block_list	*new_block;
	void			*ptr;

	assert(size > 0);
	assert(data);
	a = (t_arena *)data;
	if (!a || !a->blocks)
		return (NULL);
	if (a->used_memory & (sizeof(void *) - 1))
		a->used_memory += sizeof(void *) - (a->used_memory % sizeof(void *));
	if (a->used_memory + size > a->capacity || !a->blocks->mem_start)
	{
		if (size > a->capacity)
			new_block = _new_block(size);
		else
			new_block = _new_block(a->capacity);
		if (!new_block)
			return (NULL);
		_list_add_front(&a->blocks, new_block);
		a->used_memory = 0;
	}
	ptr = a->blocks->mem_start + a->used_memory;
	a->used_memory += size;
	return (ptr);
}

t_alloc	*new_arena_allocator(size_t size)
{
	t_alloc	*arena_allocator;

	assert(size > 0);
	arena_allocator = malloc(sizeof(t_alloc));
	if (!arena_allocator)
		return (NULL);
	*arena_allocator = (t_alloc){
		.data = _new_arena_data(size),
		.alloc_fn = arena_alloc_fn,
		.free_fn = arena_free_fn,
	};
	if (!arena_allocator->data)
		return (free(arena_allocator), NULL);
	return (arena_allocator);
}
