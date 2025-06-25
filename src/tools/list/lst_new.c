#include "tools/list.h"

t_list	*lst_new(t_alloc *alloc, void *content)
{
	t_list	*new_node;

	new_node = mem_alloc(alloc, sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
