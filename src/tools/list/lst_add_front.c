#include "tools/list.h"

void	lst_add_front(t_list **list, t_list *new_node)
{
	if (*list)
		new_node->next = *list;
	*list = new_node;
}
