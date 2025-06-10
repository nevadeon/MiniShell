#include "executing.h"

t_pid_list	*lst_pid_new(t_alloc *alloc, pid_t pid)
{
	t_pid_list	*new_node;

	new_node = mem_alloc(alloc, sizeof(t_pid_list));
	if (!new_node)
		return (NULL);
	new_node->pid = pid;
	new_node->next = NULL;
	return (new_node);
}
