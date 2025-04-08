#include "umgc.h"
#include "str.h"

static t_mgc	**_umgcs_head(void)
{
	static t_mgc	*mgcs[E_LFT_LAST_INDEX] = {0};

	return (mgcs);
}

static t_mgc	*_umgc_head(t_lftime lft)
{
	t_mgc	**mgcs;

	mgcs = _umgcs_head();
	if (!mgcs[lft])
	{
		mgcs[lft] = calloc(1, sizeof(t_mgc));
		if (!mgcs[lft])
			return (NULL);
		mgcs[lft]->arena = NULL;
		mgcs[lft]->first = NULL;
		mgcs[lft]->last = NULL;
	}
	return (mgcs[lft]);
}

void	*umgc_alloc(t_lftime lft, size_t size)
{
	void	*new_block;
	t_mgc	*mgc;
	t_arena	*arena;
	void	*tmp;

	mgc = _umgc_head(lft);
	arena = mgc->arena;
	if (!arena)
	{
		arena = malloc(sizeof(t_arena));
		if (!arena)
			return NULL;
		arena->block_size = ARENA_BLOC_SIZE;
		arena->arena = calloc(1, arena->block_size);
		if (!arena->arena)
		{
			free(arena);
			return NULL;
		}
		arena->used_memory = 0;
		mgc->arena = arena;
	}
	while (arena->used_memory + size > arena->block_size)
	{
		tmp = arena->arena;
		new_block = calloc(1, arena->block_size * 2);
		free(tmp);
		arena->arena = new_block;
		arena->block_size *= 2;
	}
	mgc->arena->used_memory += size;
	return ((char *)mgc->arena->arena + mgc->arena->used_memory - size);
}

void	umgc_add_block(t_lftime lft, void *block)
{
	t_mgc_block_list	*new_block;
	t_mgc				*mgc;

	mgc = _umgc_head(lft);
	new_block = calloc(1, sizeof(t_mgc_block_list));
	if (!new_block)
		exit(EXIT_FAILURE);
	new_block->block = block;
	new_block->next = NULL;
	if (mgc->last)
		mgc->last->next = new_block;
	mgc->last = new_block;
	if (!mgc->first)
		mgc->first = new_block;
}

void	umgc_free(t_lftime lft)
{
	t_mgc_block_list	*current;
	t_mgc_block_list	*tmp;
	t_mgc				**mgcs;

	mgcs = _umgcs_head();
	if (!mgcs[lft])
		return ;
	current = mgcs[lft]->first;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(tmp->block);
		tmp->block = NULL;
		free(tmp);
		tmp = NULL;
	}
	free(mgcs[lft]->arena->arena);
	free(mgcs[lft]->arena);
	free(mgcs[lft]);
	mgcs[lft] = NULL;
}

void	umgc_free_all(void)
{
	size_t	index;

	index = 0;
	while (index < E_LFT_LAST_INDEX)
	{
		umgc_free((t_lftime)index);
		index++;
	}
}
// add arena
// add uuid