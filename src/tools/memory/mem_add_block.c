#include "mem.h"
#include "list.h"

t_list	**get_mgc_head(t_lifetime lft)
{
	static t_list *mgc_heads[E_LFT_LAST_INDEX] = {0};

	if (lft >= E_LFT_LAST_INDEX || lft < 0)
		exit(666);
	return (&mgc_heads[lft]);
}

static t_list	*_lst_new(void *content)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

void	mem_add_block(t_lifetime lft, void *ptr)
{
	lst_add_front(get_mgc_head(lft), _lst_new(ptr));
}
