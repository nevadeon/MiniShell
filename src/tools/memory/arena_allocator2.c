#include <stdlib.h>
#include "arena_allocator.h"

bool	arena_check_fn(void *data)
{
	t_arena	*arena;

	arena = (t_arena *)data;
	return (arena && arena->blocks && arena->blocks->mem_start);
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
	t_arena	*arena;

	if (!data)
		return ;
	arena = (t_arena *)data;
	_list_clear(&arena->blocks);
	arena->blocks = NULL;
	arena->used_memory = 0;
	arena->capacity = 0;
	free(arena);
}
