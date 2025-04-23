#include "mem.h"
#include "list.h"

t_arena	*get_arena(t_lifetime lft)
{
	static t_arena	arenas[E_LFT_LAST_INDEX] = {0};

	if (lft >= E_LFT_LAST_INDEX || lft < 0)
		exit(666);
	return (&arenas[lft]);
}

static t_list	*_lst_new_block(size_t size)
{
	t_list	*new_node;
	t_byte	*block;

	block = calloc(1, size);
	if (block == NULL)
		exit(666);
	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		exit(666);
	new_node->content = block;
	new_node->next = NULL;
	return (new_node);
}

void	*mem_alloc(t_lifetime lft, size_t size)
{
	t_arena_list	**head;
	t_arena			*arena;
	size_t			used_memory;

	arena = get_arena(lft);
	head = &arena->head;
	used_memory = arena->used_memory;
	if (*head == NULL)
		*head = (t_arena_list *)_lst_new_block(ARENA_BLOCK_SIZE);
	if (*head == NULL)
		exit(666);
	if (used_memory + size > ARENA_BLOCK_SIZE)
	{
		if (size > ARENA_BLOCK_SIZE)
			lst_add_front((t_list **)head, _lst_new_block(size));
		else
			lst_add_front((t_list **)head, _lst_new_block(ARENA_BLOCK_SIZE));
		used_memory = 0;
	}
	if ((used_memory & (sizeof(void *) - 1)) != 0)
		used_memory += sizeof(void *) - (used_memory & (sizeof(void *) - 1));
	used_memory += size;
	arena->used_memory = used_memory;
	return ((*head)->block + used_memory - size);
}
