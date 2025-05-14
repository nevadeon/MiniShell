#include <stdio.h>
#include "minishell.h"

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

void	increase_shlvl(void)
{
	int	shlvl;

	shlvl = str_atoi(env_get_var_value("SHLVL"));
	shlvl++;
	env_set_var_value("SHLVL", num_itoa(shlvl));
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		prompt[PATH_MAX + 20];

	env_set(envp);
	increase_shlvl();
	while (argc == 1)
	{
		input = readline(readline_prompt(prompt, PATH_MAX + 20));
		if (input[0] != '\0')
			add_history(input);
		mem_add_block(E_LFT_TASK, input);
		if (str_equals(input, "exit"))
			break ;
		handle_command(input);
	}
	if (argc > 1)
		handle_command(_argv_to_input(argc, argv));
	mem_free_all();
	rl_clear_history();
	return (0);
}
