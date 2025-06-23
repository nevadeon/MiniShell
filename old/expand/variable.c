#include "parsing.h"
#include "char.h"
#include "env.h"
#include "str.h"

static int	_get_var_len(char *input)
{
	size_t	index;

	index = 0;
	assert(input);
	str_escape(input, &index, '{', '}');
	if (index != 0)
		return (index);
	if (input[0] != '_' && !char_isalpha(input[0]))
		return (0);
	while (char_isalnum(input[index]) || input[index] == '_')
		index++;
	return (index - 1);
}

static int	_expand_variable(t_alloc *alloc, char **input, size_t index)
{
	size_t	var_start;
	size_t	var_end;
	bool	bracket;
	char	*var_value;

	var_start = index + 1;
	bracket = ((*input)[var_start] == '{');
	var_end = var_start + _get_var_len(*input + var_start) + 1;
	if (bracket && (*input)[var_end - 1] != '}')
		exit(666); // todo handle only one bracket
	var_value = env_get_var_value(str_extract(alloc, *input, var_start + bracket, var_end - bracket), NULL);
	return (str_replace(alloc, (t_replace){\
		.str = input,
		.rep = var_value,
		.start = var_start - 1,
		.end = var_end
	}));
}

void	expand_variables(t_alloc *alloc, char **input)
{
	size_t	index;

	index = 0;
	while ((*input)[index])
	{
		str_escape((*input), &index, '\'', '\'');
		if ((*input)[index] == '$')
		{
			index += _expand_variable(alloc, input, index);
		}
		else
			index++;
	}
}
