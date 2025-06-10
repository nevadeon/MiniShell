#include "minishell.h"
#include "env.h"

static void	_override_var(t_alloc *alloc, char **word, t_var var)
{
	char	*var_name;
	size_t	var_name_len;
	char	*var_name_value;

	var_name_len = (var.name_end - var.name_start) + 1;
	var_name = mem_alloc(alloc, ((var_name_len) + 1) * sizeof(char));
	var_name = str_memcpy(var_name, *word + var.name_start, var_name_len - 1);
	var_name[var_name_len - 1] = '\0';
	var_name_value = env_get_var_value(alloc, var_name);
	str_replace(alloc, (t_replace) {word, var_name_value, var.start, var.end});
}

static bool	_is_valid_var_name(char *word, size_t index, size_t var_name_start)
{
	return (word[index] && ((index == var_name_start && (char_isalpha(word[index]) || word[index] == '_')) || (index != var_name_start && (char_isalnum(word[index]) || word[index] == '_'))));
}

void	expand_variable(t_alloc *alloc, char **word)
{
	size_t	index;
	t_var	var;
	bool	found;

	index = 0;
	do
	{
		while ((*word)[index] && (*word)[index] != '$' && handle_escape(*word, &index, '\''))
			index++;
		found = (*word)[index] == '$';
		if (!found)
			return ;
		var.start = index++;
		var.bracketed = (*word)[index] == '{';
		index += var.bracketed;
		var.name_start = index;
		while (_is_valid_var_name(*word, index, var.name_start))
			index++;
		var.name_end = index;
		if (var.bracketed && ((*word)[index]) != '}')
			exit(666); // TODO HANDLE ERROR
		var.end = var.name_end + (var.bracketed && (*word)[index] == '}');
		if (index != var.start + 1)
			_override_var(alloc, word, var);
	} while (found);
}

void	expand(t_alloc *alloc, char **word, char **input)
{
	expand_variable(alloc, word);
	expand_tilde(alloc, word);
	expand_wildcard(alloc, input, word);
}
