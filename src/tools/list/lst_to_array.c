#include "tools/list.h"

void	**lst_to_array(t_alloc *alloc, t_list *list)
{
	void	**tab;
	int		i;

	if (!list)
		return (NULL);
	tab = mem_alloc(alloc, sizeof(char *) * (lst_len(list) + 1));
	i = 0;
	while (list)
	{
		tab[i++] = list->content;
		list = list->next;
	}
	tab[i] = NULL;
	return (tab);
}
