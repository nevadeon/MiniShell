#include "list.h"
#include "mem.h"

void	**lst_to_tab(t_lifetime lft, t_list *list)
{
	void	**tab;
	int		i;

	tab = mem_alloc(lft, sizeof(char *) * (lst_len(list) + 1));
	i = 0;
	while (list)
	{
		tab[i++] = list->content;
		list = list->next;
	}
	tab[i + 1] = NULL;
	return (tab);
}
