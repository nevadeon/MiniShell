// #include "minishell.h"
// #include "builtins.h"

// int	builtin_echo(__attribute__((unused)) t_alloc *alloc, t_str_list *args)
// {
// 	t_str_list	*current;
// 	bool		newline;

// 	newline = true;
// 	if (!args || !args->content)
// 		return (printf("\n"), EXIT_SUCCESS);
// 	current = args;
// 	newline = !str_equals(current->content, "-n");
// 	if (!newline)
// 		current = current->next;
// 	while (current)
// 	{
// 		printf("%s", current->content);
// 		current = current->next;
// 		if (current && current->content)
// 			printf(" ");
// 	}
// 	if (newline)
// 		printf("\n");
// 	return (EXIT_SUCCESS);
// }
