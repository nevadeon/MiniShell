#include <stdio.h>
#include "minishell.h"
#include "signals.h"

void	increase_shlvl(t_ctx *ctx)
{
	int	shlvl;

	shlvl = str_atoi(env_get_var_value(*ctx->env, "SHLVL"));
	shlvl++;
	env_set_var_value(
		ctx, str_vjoin(*ctx->prog, 2, "SHLVL=", num_itoa(*ctx->prog, shlvl)));
}

void	handle_command(t_ctx *ctx, char *input)
{
	t_ast	*ast;

	ctx->last_error_type = E_NONE;
	ast = parsing(ctx, input);
	if (!ast || ctx->last_error_type)
		return ;
	ctx->last_exit_code = 0;
	// execute_ast(ctx, ast);
	toggle_signal(ctx, S_PARENT);
}

void	input_loop(t_ctx *ctx)
{
	char	*input;
	t_alloc	*alloc_cmd;

	while (1)
	{
		alloc_cmd = new_mgc_allocator(ARENA_BLOCK_SIZE);
		ctx->cmd = &alloc_cmd;
		input = readline(readline_prompt(*ctx->cmd));
		if (!input)
			break ;
		if (input[0] != '\0')
			add_history(input);
		handle_command(ctx, input);
		free_allocator(ctx->cmd);
		free(input);
	}
	printf("exit\n");
	free_allocator(ctx->cmd);
	free(input);
}

static t_ctx	*_new_ctx(t_alloc **alloc, char ***envp)
{
	t_ctx	*ctx;

	ctx = mem_alloc(*alloc, sizeof(t_ctx));
	*ctx = (t_ctx){
		.prog = alloc,
		.env = envp,
		.last_error_type = E_NONE,
		.last_exit_code = 0,
	};
	return (ctx);
}

int	main(int argc, __attribute__((unused)) char **argv, char **envp)
{
	t_ctx				*ctx;
	t_alloc				*alloc;

	rl_catch_signals = 0;
	if (argc != 1)
		return (EXIT_FAILURE);
	alloc = new_mgc_allocator(ARENA_BLOCK_SIZE);
	ctx = _new_ctx(&alloc, &envp);
	increase_shlvl(ctx);
	toggle_signal(ctx, S_PARENT);
	input_loop(ctx);
	free_allocator(ctx->prog);
	rl_clear_history();
	return (0);
}
