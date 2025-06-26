#include "tools/list.h"
#include "stdio.h"

void	lst_print(t_list *list, t_print_fn print_function)
{
	t_list	*current;

	current = list;
	while (current)
	{
		print_function(current->content);
		current = current->next;
		if (current)
			printf(", ");
	}
}
