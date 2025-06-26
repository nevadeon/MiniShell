#include "tools/str.h"

static int	_count_words(const char *s, char c)
{
	int	nb_words;

	nb_words = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			nb_words++;
		s++;
	}
	return (nb_words);
}

static char	*_strdup_to_c(t_alloc *alloc, const char **s, char c)
{
	char	*cpy;
	int		cpy_len;
	int		i;

	cpy_len = 0;
	while ((*s)[cpy_len] && (*s)[cpy_len] != c)
		cpy_len++;
	cpy = mem_alloc(alloc, sizeof(char) * (cpy_len + 1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (i < cpy_len)
	{
		cpy[i] = **s;
		(*s)++;
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**str_split(t_alloc *alloc, char const *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	tab = mem_alloc(alloc, sizeof(char *) * (_count_words(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			tab[i] = _strdup_to_c(alloc, &s, c);
			if (tab[i] == NULL)
				return (NULL);
			i++;
		}
	}
	tab[i] = (char *) NULL;
	return (tab);
}
