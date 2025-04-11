#include "test.h"

void	test_memory(void)
{
	char *s;
	int i;

	i = 0;
	while(i++ < 10)
	{
		s = mem_alloc(E_LFT_PROG, 10);
		s = mem_alloc(E_LFT_TASK, 10);
		s = mem_alloc(E_LFT_FUNC, 10);
	}

	s = mem_alloc(E_LFT_PROG, ARENA_BLOCK_SIZE + 1);
	s = mem_alloc(E_LFT_TASK, ARENA_BLOCK_SIZE + 1);
	s = mem_alloc(E_LFT_FUNC, ARENA_BLOCK_SIZE + 1);

	mem_free_instance(E_LFT_PROG);
	mem_free_instance(E_LFT_PROG);
	mem_free_instance(E_LFT_TASK);
	mem_free_instance(E_LFT_TASK);
	mem_free_instance(E_LFT_FUNC);
	mem_free_instance(E_LFT_FUNC);
	mem_free_all();
	mem_free_all();

	s = mem_alloc(E_LFT_PROG, 100);
	mem_free_all();
	assert(*(get_mgc_head(E_LFT_PROG)) == NULL);
	assert(get_arena(E_LFT_PROG)->head == NULL);

	mem_add_block(E_LFT_PROG, strdup("plouc1"));
	mem_add_block(E_LFT_PROG, strdup("plouc2"));
	mem_add_block(E_LFT_TASK, strdup("plouc3"));
	mem_add_block(E_LFT_TASK, strdup("plouc4"));
	mem_add_block(E_LFT_FUNC, strdup("plouc5"));
	mem_add_block(E_LFT_FUNC, strdup("plouc6"));
	mem_free_all();

	printf("All memory tests passed 🗸\n");
}
