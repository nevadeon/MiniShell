#ifndef SORT_H
# define SORT_H

typedef struct s_list t_list;

t_list	*ft_qsort(t_list *list, int (*f)(void *, void *));
int		ascii_sort(void *a, void *b);

#endif
