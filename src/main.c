#include <stdio.h>
#include "minishell.h"
#include "signals.h"

static char	*_argv_to_input(int argc, char **argv)
{
	char	*input;
	int		i;

	i = 1;
	input = mem_alloc(E_LFT_TASK, 1);
	while (i < argc)
	{
		input = str_vjoin(E_LFT_TASK, 2, input, argv[i]);
		if (i != argc)
			input = str_vjoin(E_LFT_TASK, 2, input, " ");
		i++;
	}
	return (input);
}

void	input_loop(void)
{
	char	prompt[PATH_MAX + 20];
	char	*input;

	while (1)
	{
		input = readline(readline_prompt(prompt, PATH_MAX + 20));
		if (g_signal == SIGINT)
		{
			mem_free_instance(E_LFT_TASK);
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
		mem_add_block(E_LFT_TASK, input);
		if (str_equals(input, "exit"))
			break ;
		handle_command(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;

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
		handle_command(_argv_to_input(argc, argv));
	mem_free_all();
	rl_clear_history();
	return (0);
}
