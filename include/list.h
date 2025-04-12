#ifndef LIST_H
# define LIST_H

# include <stdlib.h>

typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}	t_list;

typedef void	(*t_delete_function)(void *);

t_list	*lst_new(void *content);
void	lst_add_front(t_list **list, t_list *new_node);

#endif
