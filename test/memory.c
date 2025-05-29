#include "test.h"

bool	test_memory(void)
{
	t_allocator	alloc;

	alloc = make_arena_allocator(ARENA_BLOCK_SIZE);
	assert(check_allocator(&alloc));
	assert(((t_arena *)alloc.data)->capacity == ARENA_BLOCK_SIZE);
	assert(((t_arena *)alloc.data)->used_memory == 0);

	//return address test
	__attribute__((unused)) void	*origin;
	__attribute__((unused)) void	*dump;
	origin = ((t_arena *)alloc.data)->blocks->mem_start;
	mem_alloc(&alloc, 3);
	dump = mem_alloc(&alloc, 5);
	assert(dump == (origin + 8));
	dump = mem_alloc(&alloc, 1);
	assert(dump == (origin + 16));

	//block overflow test
	int i = 0;
	while (++i <= 20)
		mem_alloc(&alloc, ARENA_BLOCK_SIZE / 4);

	//oversize test
	mem_alloc(&alloc, ARENA_BLOCK_SIZE + 1);

	//free test
	free_allocator(&alloc);
	assert(!alloc.data);
	assert(!alloc.alloc_fn);
	assert(!alloc.check_fn);
	assert(!alloc.free_fn);

	printf("All memory tests passed 🥰\n");
	return (EXIT_SUCCESS);
}
