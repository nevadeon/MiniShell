#include <stdlib.h>
#include "arena_allocator.h"

bool	arena_check_fn(void *data)
{
	t_dynamic_arena	*arena;

	assert(data);
	arena = (t_dynamic_arena *)data;
	if (arena && arena->blocks && arena->blocks->mem_start)
		return (true);
	return (false);
}

static void	_list_clear(t_block_list **list)
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

void	arena_free_fn(void *data)
{
	t_dynamic_arena	*arena;

	if (!data)
		return ;
	arena = (t_dynamic_arena *)data;
	_list_clear(&arena->blocks);
	arena->blocks = NULL;
	arena->used_memory = 0;
	arena->capacity = 0;
	free(arena);
}
