#include "list.h"

void	lst_clear(t_list **list, t_delete_function delete)
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
