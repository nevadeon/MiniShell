#ifndef MEM_H
# define MEM_H

# include <stdlib.h>
# include "int.h"
# include "list.h"

# define ARENA_BLOCK_SIZE 4096

typedef enum E_LIFETIME
{
	E_LFT_FUNC = 0,
	E_LFT_PROG = 1,
	E_LFT_TASK = 2,
	E_LFT_LAST_INDEX = 3
}	t_lifetime;

typedef struct s_arena_list
{
	struct s_arena_list	*next;
	t_byte				*block;
}	t_arena_list;

typedef struct s_arena
{
	t_arena_list	*head;
	size_t			used_memory;
}	t_arena;

void			*mem_alloc(t_lifetime lft, size_t size);
void			mem_add_block(t_lifetime lft, void *ptr);
void			mem_free_instance(t_lifetime lft);
void			mem_free_all(void);

/**
 * @brief This function is for mem management intern logic. Do not call it
 */
t_arena			*get_arena(t_lifetime lft);
/**
 * @brief This function is for mem management intern logic. Do not call it
 */
t_list			**get_mgc_head(t_lifetime lft);

#endif
