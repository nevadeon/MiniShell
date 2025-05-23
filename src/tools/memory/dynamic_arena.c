#include <stdlib.h>
#include "dynamic_arena.h"

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

t_dynamic_arena *new_dynamic_arena_data(size_t capacity)
{
	t_dynamic_arena	*arena;

	assert(capacity > 0);
	arena = malloc(sizeof(t_dynamic_arena));
	if (!arena)
		return (NULL);
	*arena = (t_dynamic_arena){
		.blocks = _new_block(capacity),
		.capacity = capacity,
		.used_memory = 0,
	};
	return (arena);
}

void	*dynamic_arena_alloc_fn(void *data, size_t size)
{
	t_dynamic_arena	*a;
	t_block_list	*new_block;
	void			*ptr;

	assert(data);
	assert(size > 0);
	a = (t_dynamic_arena *)data;
	if (!a->blocks)
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

bool	dynamic_arena_check_fn(void *data)
{
	t_dynamic_arena	*arena;

	assert(data);
	arena = (t_dynamic_arena *)data;
	if (arena && arena->blocks && arena->blocks->mem_start)
		return (true);
	return (false);
}

static void	list_clear(t_block_list **list)
{
	t_block_list	*node;
	t_block_list	*temp;

	if (list == NULL)
		return ;
	node = *(list);
	while (node != NULL)
	{
		free(node->mem_start);
		temp = node->next;
		free(node);
		node = temp;
	}
	*list = NULL;
}

void	dynamic_arena_free_fn(void *data)
{
	t_dynamic_arena	*arena;

	if (!data)
		return ;
	arena = (t_dynamic_arena *)data;
	list_clear(&arena->blocks);
	arena->blocks = NULL;
	arena->used_memory = 0;
	arena->capacity = 0;
	free(arena);
}

t_allocator	make_dynamic_arena_allocator(size_t size)
{
	t_allocator	dynamic_allocator;

	dynamic_allocator = (t_allocator){
		.data = new_dynamic_arena_data(size),
		.alloc_fn = dynamic_arena_alloc_fn,
		.check_fn = dynamic_arena_check_fn,
		.free_fn = dynamic_arena_free_fn,
	};
	return (dynamic_allocator);
}
