#include "minishell.h"
#include "builtins.h"

int	builtin_echo(__attribute__((unused)) t_alloc *alloc, char **args)
{
	bool	newline;
    int     i;

	newline = false;
	if (!args[1])
    {
		printf("\n");
        exit(EXIT_SUCCESS);
    }
	newline = str_cmp(args[1], "-n") == 0;
    i = 0 + newline;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
            printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	exit(EXIT_SUCCESS);
}
