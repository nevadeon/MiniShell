#include <stdio.h>
#include "minishell.h"
#include "signals.h"

static char	*_argv_to_input(t_allocator *alloc, int argc, char **argv)
{
	char	*input;
	int		i;

	i = 1;
	input = mem_alloc(alloc, 1);
	while (i < argc)
	{
		input = str_vjoin(alloc, 2, input, argv[i]);
		if (i != argc)
			input = str_vjoin(alloc, 2, input, " ");
		i++;
	}
	return (input);
}

void	increase_shlvl(t_allocator *alloc)
{
	int	shlvl;

	shlvl = str_atoi(env_get_var_value(alloc, "SHLVL"));
	shlvl++;
	env_set_var_value(alloc, "SHLVL", num_itoa(alloc, shlvl));
}

void	input_loop(void)
{
	t_allocator		alloc_cmd;
	char			*input;
	char			prompt[PATH_MAX + 20];

	while (1)
	{
		alloc_cmd = make_arena_allocator(ARENA_BLOCK_SIZE);
		input = readline(readline_prompt(prompt, PATH_MAX + 20));
		if (g_signal == SIGINT)
		{
			free_allocator(&alloc_cmd);
			g_signal = 0;
			free(input);
			continue ;
		}
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (input[0] != '\0')
			add_history(input);
		if (str_equals(input, "exit"))
			break ;
		handle_command(&alloc_cmd, input);
		free_allocator(&alloc_cmd);
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	t_allocator			alloc_prog;

	env_set(envp);
	alloc_prog = make_arena_allocator(ARENA_BLOCK_SIZE);
	increase_shlvl(&alloc_prog);
	memset(&sa, 0, sizeof(struct sigaction));
	env_set(envp);
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	if (argc == 1)
		input_loop();
	else
		handle_command(&alloc_prog, _argv_to_input(&alloc_prog, argc, argv));
	free_allocator(&alloc_prog);
	rl_clear_history();
	return (0);
}