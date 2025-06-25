#include "tools/list.h"

void	lst_add_back(t_list **list, t_list *new_node)
{
	t_list	*current;

	if (!*list)
	{
		*list = new_node;
		return ;
	}
	current = *list;
	while (current->next)
		current = current->next;
	current->next = new_node;
}
