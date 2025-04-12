#include "list.h"
#include "mem.h"

t_list	*lst_new(t_lifetime lft, void *content)
{
	t_list	*new_node;

	new_node = mem_alloc(lft, sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
