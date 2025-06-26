/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 15:45:44 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "allocators/arena_allocator.h"

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
