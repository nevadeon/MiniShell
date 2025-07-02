#include "tools/str.h"

bool	str_escape(char *s, size_t *index, char start, char end)
{
	assert(s);
	assert(index);
	if (!s[*index] || s[*index] != start)
		return (true);
	(*index)++;
	while (s[*index] && s[*index] != end)
	{
		if (s[*index] == '\\' && s[*index + 1])
			(*index)++;
		(*index)++;
	}
	if (s[*index] == end)
	{
		(*index)++;
		return (true);
	}
	return (false);
}

bool	str_escape_with_context(char *s, size_t *index, char quote_char)
{
	char	current_quote;

	if (!s[*index])
		return (true);
	current_quote = s[*index];
	if (current_quote != '\'' && current_quote != '"')
		return (true);
	if (quote_char != '\0' && current_quote != quote_char)
	{
		(*index)++;
		return (true);
	}
	(*index)++;
	while (s[*index] && s[*index] != current_quote)
	{
		if (s[*index] == '\\' && s[*index + 1])
			(*index)++;
		(*index)++;
	}
	if (s[*index] == current_quote)
	{
		(*index)++;
		return (true);
	}
	return (false);
}
