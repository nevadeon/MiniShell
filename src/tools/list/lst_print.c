#include "list.h"
#include "stdio.h"

void	lst_print(t_list *list, void(*print_function)(void *))
{
	t_list	*current;

	current = list;
	while (current)
	{
		print_function(current);
		current = current->next;
		if (current)
			printf(", ");
	}
}
