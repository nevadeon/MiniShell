#include "tools/sort.h"

static t_list	*\
	_merge_sorted_lists(t_list *smaller, t_list *equal, t_list *greater)
{
	t_list	*result;
	t_list	*tmp;

	result = smaller;
	if (smaller)
	{
		tmp = smaller;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = equal;
	}
	else
		result = equal;
	if (equal)
	{
		tmp = equal;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = greater;
	}
	else if (!smaller)
		result = greater;
	return (result);
}

static void	_partition_list(t_list *list, t_list *pivot, int (*f)(void *, void *),
						t_list **smaller, t_list **equal, t_list **greater)
{
	t_list	*current;
	t_list	*next;
	int		cmp_result;

	current = list;
	*smaller = NULL;
	*equal = NULL;
	*greater = NULL;
	while (current)
	{
		next = current->next;
		current->next = NULL;
		if (current == pivot)
			cmp_result = 0;
		else
			cmp_result = f(current->content, pivot->content);
		if (cmp_result < 0)
			lst_add_back(smaller, current);
		else if (cmp_result > 0)
			lst_add_back(greater, current);
		else
			lst_add_back(equal, current);
		current = next;
	}
}

t_list	*ft_qsort(t_list *list, int (*f)(void *, void *))
{
	t_list	*smaller;
	t_list	*equal;
	t_list	*greater;

	if (!list || !list->next)
		return (list);
	_partition_list(list, list, f, &smaller, &equal, &greater);
	smaller = ft_qsort(smaller, f);
	greater = ft_qsort(greater, f);
	return (_merge_sorted_lists(smaller, equal, greater));
}
