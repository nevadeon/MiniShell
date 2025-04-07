#include "mgc.h"

static t_mgc	**mgcs_head(void)
{
	static t_mgc	*mgcs[E_LFT_LAST_INDEX] = {};

	return (mgcs);
}

static t_mgc	*mgc_head(t_lftime lft)
{
	t_mgc	**mgcs;

	mgcs = mgcs_head();
	if (!mgcs[lft])
	{
		mgcs[lft] = calloc(1, sizeof(t_mgc));
		if (!mgcs[lft])
			return (NULL);
		mgcs[lft]->first = NULL;
		mgcs[lft]->last = NULL;
	}
	return (mgcs[lft]);
}

void	*mgc_alloc(t_lftime lft, size_t nb_elem, size_t size)
{
	void	*block;

	block = calloc(nb_elem, size);
	if (!block)
		return (NULL);
	mgc_add_block(lft, block);
	return (block);
}

void	mgc_add_block(t_lftime lft, void *block)
{
	t_mgc_block_list	*new_block;
	t_mgc				*mgc;

	mgc = mgc_head(lft);
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

void	mgc_free(t_lftime lft)
{
	t_mgc_block_list	*current;
	t_mgc_block_list	*tmp;
	t_mgc				**mgcs;

	mgcs = mgcs_head();
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
	free(mgcs[lft]);
	mgcs[lft] = NULL;
}

void	mgc_free_all(void)
{
	size_t	index;

	index = 0;
	while (index < E_LFT_LAST_INDEX)
	{
		mgc_free((t_lftime)index);
		index++;
	}
}
