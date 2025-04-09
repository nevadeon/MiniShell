#ifndef MGC_H
# define MGC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

# define ARENA_BLOC_SIZE 65536

typedef enum E_LIFETIME
{
	E_LFT_FUNC = 0,
	E_LFT_PROG = 1,
	E_LFT_FEATURE = 2,
	E_LFT_LAST_INDEX = 3
}	t_lftime;

typedef struct s_mgc_block_list
{
	void					*block;
	struct s_mgc_block_list	*next;
}	t_mgc_block_list;

typedef struct s_arena
{
	void	*arena;
	size_t	block_size;
	size_t	used_memory;
}	t_arena;

typedef struct s_mgc
{
	t_arena				*arena;
	t_mgc_block_list	*first;
	t_mgc_block_list	*last;
}	t_mgc;


void		*umgc_alloc(t_lftime lft, size_t size);
void		umgc_add_block(t_lftime lft, void *block);
void		umgc_free(t_lftime lft);
void		umgc_free_all(void);

#endif
