#ifndef MGC_H
# define MGC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef enum E_LIFETIME
{
	E_FUNC = 0,
	E_PROG = 1,
	E_FEATURE = 2,
	E_LFT_LAST_INDEX = 3
}	t_lftime;

typedef struct s_mgc_block_list
{
	void					*block;
	struct s_mgc_block_list	*next;
}	t_mgc_block_list;

typedef struct s_mgc
{
	struct s_mgc_block_list	*first;
	struct s_mgc_block_list	*last;
}	t_mgc;


void		mgc_init(t_lftime lft);
void		*mgc_alloc(t_lftime lft, size_t nb_elem, size_t size);
void		mgc_add_block(t_lftime lft, void *block);
void		mgc_free(t_lftime lft);
void		mgc_free_all(void);

#endif