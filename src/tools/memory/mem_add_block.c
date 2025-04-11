#include "mem.h"

t_list	**get_mgc_head(t_lifetime lft)
{
	static t_list *mgc_heads[E_LFT_LAST_INDEX] = {0};

	if (lft >= E_LFT_LAST_INDEX || lft < 0)
		exit(666);
	return (&mgc_heads[lft]);
}

void	mem_add_block(t_lifetime lft, void *ptr)
{
	lst_add_front(get_mgc_head(lft), lst_new(ptr));
}
