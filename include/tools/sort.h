#ifndef SORT_H
# define SORT_H

# include "tools/str.h"
# include "tools/list.h"

typedef struct s_list	t_list;

typedef struct s_partition
{
	t_list	*list;
	t_list	*pivot;
	int		(*compare)(void *, void *);
	t_list	**smaller;
	t_list	**equal;
	t_list	**greater;
}	t_partition;

t_list	*ft_qsort(t_list *list, int (*f)(void *, void *));
int		ascii_sort(void *a, void *b);
int		ascii_lexic_cmd(const char *a, const char *b);

#endif
