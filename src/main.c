#include <stdio.h>
#include "minishell.h"
#include "signals.h"

void	increase_shlvl(t_alloc *alloc)
{
	int	shlvl;

	shlvl = str_atoi(env_get_var_value(alloc, "SHLVL"));
	shlvl++;
	env_set_var_value(alloc, "SHLVL", num_itoa(alloc, shlvl));
}

void	input_loop(t_alloc *alloc_prog)
{
	char	*input;
	t_alloc	*alloc_cmd;

	while (1)
	{
		alloc_cmd = new_arena_allocator(ARENA_BLOCK_SIZE);
		input = readline(readline_prompt(alloc_cmd));
		if (!input)
			break ;
		if (input[0] != '\0')
			add_history(input);
		if (str_equals(input, "exit"))
			break ;
		handle_command(&alloc_prog, &alloc_cmd, input);
		free_allocator(&alloc_cmd);
		free(input);
	}
	printf("exit\n");
	free_allocator(&alloc_cmd);
}

int	main(int argc, __attribute__((unused)) char **argv, char **envp)
{
	struct sigaction	sa;
	t_alloc				*alloc_prog;

	rl_catch_signals = 0;
	if (argc != 1)
		return (EXIT_FAILURE);
	env_set(envp);
	alloc_prog = new_arena_allocator(ARENA_BLOCK_SIZE);
	increase_shlvl(alloc_prog);
	memset(&sa, 0, sizeof(struct sigaction));
	env_set(envp);
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	input_loop(alloc_prog);
	free_allocator(&alloc_prog);
	rl_clear_history();
	return (0);
}
