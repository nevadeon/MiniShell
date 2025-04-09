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

int	main(int argc, char **argv,__attribute__((unused)) char **envp)
{
	char		*input;
	char		prompt[PATH_MAX + 20];

	env_set(envp);
	while (argc == 1)
	{
		input = readline(_readline_prompt(prompt, PATH_MAX + 20));
		if (input[0] != '\0')
			add_history(input);
		umgc_add_block(E_LFT_FEATURE, input);
		if (str_equals(input, "exit"))
			break ;
		handle_command(input);
	}
	if (argc > 1)
		printf("handle command %s\n", argv[0]);
	umgc_free_all();
	rl_clear_history();
	return (0);
}