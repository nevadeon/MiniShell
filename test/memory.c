#include "test.h"

bool	test_memory(void)
{
	int		i;
	__attribute__((unused)) char	*s;

	i = 0;
	while (++i <= 20)
	{
		s = mem_alloc(E_LFT_PROG, ARENA_BLOCK_SIZE / 4);
		s = mem_alloc(E_LFT_TASK, ARENA_BLOCK_SIZE / 4);
		s = mem_alloc(E_LFT_FUNC, ARENA_BLOCK_SIZE / 4);
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

	//verifying that allocated memory is correctly freed
	s = mem_alloc(E_LFT_PROG, 100);
	mem_free_all();
	assert(*(get_mgc_head(E_LFT_PROG)) == NULL);
	assert(get_arena(E_LFT_PROG)->head == NULL);
	assert(get_arena(E_LFT_PROG)->used_memory == 0);

	//memory alignment verification
	void *arena_origin = mem_alloc(E_LFT_PROG, 0);
	void *ptr1 = mem_alloc(E_LFT_PROG, sizeof(void *) + 1);
	void *ptr2 = mem_alloc(E_LFT_PROG, 1);
	assert(((ptr1 - arena_origin) % sizeof(void *)) == 0);
	assert(((ptr2 - arena_origin) % sizeof(void *)) == 0);

	mem_add_block(E_LFT_PROG, strdup("test-1"));
	mem_add_block(E_LFT_PROG, strdup("test-2"));
	mem_add_block(E_LFT_TASK, strdup("test-3"));
	mem_add_block(E_LFT_TASK, strdup("test-4"));
	mem_add_block(E_LFT_FUNC, strdup("test-5"));
	mem_add_block(E_LFT_FUNC, strdup("test-6"));
	mem_free_all();

	printf("All memory tests passed 🥰\n");
	return (EXIT_SUCCESS);
}
