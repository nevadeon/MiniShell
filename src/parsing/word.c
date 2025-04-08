#include "minishell.h"

static ssize_t	_count_chars_until(char *input, ssize_t pos, char until)
{
	while (input[pos] && input[pos] != until)
		pos++;
	if (input[pos] != until)
		return (-1);
	return (pos);
}

static ssize_t	_get_word_len(char *input)
{
	ssize_t	len;
	ssize_t	tmp;
	char	c;

	len = 0;
	c = 0;
	while (input[len] && !isspace(input[len]))
	{
		if (input[len] == '"' || input[len] == '\'')
		{
			c = input[len];
			tmp = _count_chars_until(input, len + 1, c);
			if (tmp == -1)
				return (fprintf(stderr, "%c is not closed\n", c), -1);
			len += tmp;
		}
		len++;
	}
	return (len);
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
	word = umgc_alloc(E_LFT_FEATURE, 2 * sizeof(char));
	str_memcpy(word, *input, len);
	*input += len;
	word[len] = '\0';
	if (str_len(word) == 0)
		return (word);
	return (word);
}
