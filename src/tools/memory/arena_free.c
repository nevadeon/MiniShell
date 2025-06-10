#include <stdlib.h>
#include "arena_allocator.h"

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

	arena = (t_arena *)data;
	assert(arena);
	assert(arena->blocks);
	if (!arena || !arena->blocks)
		return ;
	_list_clear(&arena->blocks);
	*arena = (t_arena){0};
	free(arena);
}
