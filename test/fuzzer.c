#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"

extern char **environ;

static t_ctx	*_new_ctx(t_alloc **alloc, char ***envp)
{
	t_ctx	*ctx;

	ctx = mem_alloc(*alloc, sizeof(t_ctx));
	*ctx = (t_ctx){
		.prog = alloc,
		.env = envp,
		.last_error_type = ERR_NONE,
		.last_exit_code = 0,
	};
	return (ctx);
}

int	LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
	t_ctx	*ctx;
	t_alloc	*prog;

	prog = new_mgc_allocator(ARENA_BLOCK_SIZE);
	ctx = _new_ctx(&prog, &environ);
	fprintf(stderr, ">>> Input: \"%.*s\" <<<\n", (int)Size, Data);
	parsing(ctx, (char **)&Data);
	free_allocator(ctx->prog);
	return 0;
}
