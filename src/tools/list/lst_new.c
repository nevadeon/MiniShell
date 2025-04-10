#include "list.h"

t_list	*lst_new(void *content)
{
	t_list	*new_node;

	new_node = calloc(1, sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
