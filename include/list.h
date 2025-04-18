#ifndef LIST_H
# define LIST_H

typedef enum e_lifetime t_lifetime;

typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}	t_list;

typedef void	(*t_delete_function)(void *);

t_list	*lst_new(t_lifetime lft, void *content);
void	lst_add_front(t_list **list, t_list *new_node);
void	lst_add_back(t_list **list, t_list *new_node);

#endif
