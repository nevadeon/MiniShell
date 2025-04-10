#include "mem.h"

static void	_del_node(void *content)
{
	free(content);
}

void	mem_free_instance(t_lifetime lft)
{
	t_list	**mgc_head;
	t_arena	*arena;

	mgc_head = get_mgc_head(lft);
	arena = get_arena(lft);
	lst_clear((t_list **)&arena->head, _del_node);
	lst_clear((t_list **)mgc_head, _del_node);
	arena->head = NULL;
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
