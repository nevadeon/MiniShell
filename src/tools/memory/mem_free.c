#include "mem.h"
#include "list.h"

static void	_del_node(void *content)
{
	free(content);
}

static void	_lst_clear(t_list **list, t_delete_function delete)
{
	t_list	*node;
	t_list	*temp;

	if (list == NULL || delete == NULL)
		return ;
	node = *(list);
	while (node != NULL)
	{
		delete(node->content);
		temp = node->next;
		free(node);
		node = temp;
	}
	*list = NULL;
}

void	mem_free_instance(t_lifetime lft)
{
	t_list	**mgc_head;
	t_arena	*arena;

	arena = get_arena(lft);
	_lst_clear((t_list **)&arena->head, _del_node);
	arena->head = NULL;
	arena->used_memory = 0;
	mgc_head = get_mgc_head(lft);
	_lst_clear((t_list **)mgc_head, _del_node);
	*mgc_head = NULL;
}

void	mem_free_all(void)
{
	int	lft;

	lft = 0;
	while (lft < E_LFT_LAST_INDEX)
	{
		mem_free_instance(lft);
		lft++;
	}
}
