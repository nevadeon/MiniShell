#include <stdio.h>
#include "minishell.h"
#include <string.h>

static char	*_readline_prompt(char *buf, size_t size)
{
	char	cwd[PATH_MAX];
	int		n;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		cwd[0] = '\0';
	n = snprintf(buf, size,
		"\033[1;32mminishell\033[0m \033[1;35m%s\033[0m \033[1;32m# \033[0m",
		cwd);
	if (n < 0 || (size_t)n >= size)
		return (NULL);
	return (buf);
}

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

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		prompt[PATH_MAX + 20];

	env_set(envp);
	while (argc == 1)
	{
		input = readline(_readline_prompt(prompt, PATH_MAX + 20));
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
