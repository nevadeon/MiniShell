#include "executing.h"
#include "mem.h"

t_pid_list	*lst_pid_new(pid_t pid)
{
	t_pid_list	*new_node;

	new_node = mem_alloc(E_LFT_TASK, sizeof(t_pid_list));
	if (!new_node)
		return (NULL);
	new_node->pid = pid;
	new_node->next = NULL;
	return (new_node);
}
