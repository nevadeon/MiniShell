/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nevadeon <github@glhf.slmail.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:43:20 by nevadeon          #+#    #+#             */
/*   Updated: 2025/06/26 17:10:35 by nevadeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void	_partition_list(t_partition *p)
{
	t_list	*current;
	t_list	*next;
	int		cmp_result;

	current = p->list;
	*(p->smaller) = NULL;
	*(p->equal) = NULL;
	*(p->greater) = NULL;
	while (current)
	{
		next = current->next;
		current->next = NULL;
		if (current == p->pivot)
			cmp_result = 0;
		else
			cmp_result = p->compare(current->content, p->pivot->content);
		if (cmp_result < 0)
			lst_add_back(p->smaller, current);
		else if (cmp_result > 0)
			lst_add_back(p->greater, current);
		else
			lst_add_back(p->equal, current);
		current = next;
	}
}

t_list	*ft_qsort(t_list *list, int (*f)(void *, void *))
{
	t_list		*smaller;
	t_list		*equal;
	t_list		*greater;
	t_partition	partition;

	if (!list || !list->next)
		return (list);
	partition = (t_partition){list, list, f, &smaller, &equal, &greater};
	_partition_list(&partition);
	smaller = ft_qsort(smaller, f);
	greater = ft_qsort(greater, f);
	return (_merge_sorted_lists(smaller, equal, greater));
}
