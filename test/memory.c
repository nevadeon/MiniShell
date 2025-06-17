#include "test.h"

void	test_mgc(void)
{
	t_alloc *alloc;

	alloc = new_mgc_allocator(0);
	void *ptr;
	int i = 0;
	while (i < 20)
	{
		ptr = mem_alloc(alloc, 100);
		i++;
	}
	free_allocator(&alloc);
}

bool	test_memory(void)
{
	t_alloc	*alloc;

	alloc = new_arena_allocator(ARENA_BLOCK_SIZE);
	assert(((t_arena *)alloc->data)->capacity == ARENA_BLOCK_SIZE);
	assert(((t_arena *)alloc->data)->used_memory == 0);

	//return address test
	__attribute__((unused)) void	*origin;
	__attribute__((unused)) void	*dump;
	origin = ((t_arena *)alloc->data)->blocks->mem_start;
	mem_alloc(alloc, 3);
	dump = mem_alloc(alloc, 5);
	assert(dump == (origin + 8));
	dump = mem_alloc(alloc, 1);
	assert(dump == (origin + 16));

	//block overflow test
	int i = 0;
	while (++i <= 20)
		mem_alloc(alloc, ARENA_BLOCK_SIZE / 4);

	//oversize test
	mem_alloc(alloc, ARENA_BLOCK_SIZE + 1);

	//free test
	free_allocator(&alloc);
	assert(!alloc);

	test_mgc();

	printf("All memory tests passed 🥰\n");
	return (EXIT_SUCCESS);
}
