#include "minishell.h"

void	expand_tilde(char **word)
{
	char	*var_name_value;

	if ((*word)[0] == '~' && ((*word)[1] == '\0' || (*word)[1] == '/'))
	{
		var_name_value = env_get_var_value("HOME");
		str_replace(word, var_name_value, 0, 1);
	}
}
