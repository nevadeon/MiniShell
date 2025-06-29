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
		.cmd = alloc,
		.env = envp,
		.last_error_type = E_NONE,
		.last_exit_code = 0,
	};
	return (ctx);
}

int	LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
	t_ctx	*ctx;
	t_alloc	*alloc;
	char	*input;

	if (Size == 0)
		return (0);

	// for (size_t i = 0; i < Size; i++) {
	// 	unsigned char c = Data[i];
	// 	switch (c) {
	// 		case '\n': fputs("\\n", stderr); break;
	// 		case '\r': fputs("\\r", stderr); break;
	// 		case '\t': fputs("\\t", stderr); break;
	// 		case '\\': fputs("\\\\", stderr); break;
	// 		case '"':  fputs("\\\"", stderr); break;
	// 		default:
	// 			if (c < 32 || c > 126)
	// 				fprintf(stderr, "%02X", c);
	// 			else
	// 				fputc(c, stderr);
	// 	}
	// }
	// fputc('\n', stderr);

	input = malloc(Size + 1);
	if (!input)
		return (0);
	memcpy(input, Data, Size);
	input[Size] = '\0';
	alloc = new_mgc_allocator(ARENA_BLOCK_SIZE);
	ctx = _new_ctx(&alloc, &environ);
	parsing(ctx, input);
	free_allocator(&alloc);
	free(input);
	return 0;
}
