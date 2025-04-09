#include "minishell.h"

static bool	_is_ope(char *input, ssize_t *i)
{
	bool	ope;
	if ((*i) < 0)
		return (false);
	ope = (input[(*i)] == '|' || input[(*i)] == '<' || input[(*i)] == '>');
	if (ope && (*i) == 0)
		(*i)++;
	if (ope && (*i) == 1 && (input[(*i)] == '<' || input[(*i)] == '>'))
		(*i)++;
	return (ope);
}


static ssize_t	_get_word_len(char *input)
{
	ssize_t	len;
	bool	escape;

	len = 0;
	escape = false;
	while (input[len] && !isspace(input[len]) && !_is_ope(input, &len))
	{
		handle_escape(input, &len, &escape, '\'');
		handle_escape(input, &len, &escape, '"');
		len++;
	}
	if (escape)
		return (fprintf(stderr, "quote error\n"), exit(EXIT_FAILURE), 0);
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
	word = umgc_alloc(E_LFT_FEATURE, (len + 1) * sizeof(char));
	str_memcpy(word, *input, len);
	*input += len;
	word[len] = '\0';
	if (str_len(word) == 0)
		return (word);
	_remove_quotes(word);
	return (word);
}
