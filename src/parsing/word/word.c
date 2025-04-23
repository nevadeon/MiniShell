#include "minishell.h"

static bool	_is_ope(char *input, size_t *i)
{
	bool	ope;

	ope = (input[(*i)] == '|' || input[(*i)] == '<' || input[(*i)] == '>');
	if (ope && (*i) == 0)
		(*i)++;
	if (ope && (*i) == 1 && (input[(*i)] == '<' || input[(*i)] == '>'))
		(*i)++;
	return (ope);
}

static size_t	_get_word_len(char *input)
{
	size_t	len;

	len = 0;
	while (input[len]
		&& !isspace(input[len])
		&& !_is_ope(input, &len)
		&& handle_escape(input, &len, '"')
		&& handle_escape(input, &len, '\''))
		len++;
	return (len);
}

static void	_remove_quotes(char *str)
{
	char	*src;
	char	*dst;

	src = str;
	dst = str;
	while (*src)
	{
		if (*src == '"' || *src == '\'')
			src++;
		else
			*dst++ = *src++;
	}
	*dst = '\0';
}

char	*get_next_word(char **input)
{
	char	*word;
	int		len;

	while (**input && isspace(**input))
		(*input)++;
	len = _get_word_len(*input);
	if (len < 0)
		return (NULL);
	word = mem_alloc(E_LFT_TASK, (len + 1) * sizeof(char));
	str_memcpy(word, *input, len);
	*input += len;
	word[len] = '\0';
	if (str_len(word) == 0)
		return (word);
	expand(&word);
	_remove_quotes(word);
	return (word);
}
