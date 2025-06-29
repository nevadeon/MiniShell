#include "parsing.h"

static bool	handle_quote_state(char c, char *quote_char, int *inside_quotes)
{
	if (!*inside_quotes && (c == '\'' || c == '"'))
	{
		*quote_char = c;
		*inside_quotes = 1;
		return (true);
	}
	if (*inside_quotes && c == *quote_char)
	{
		*inside_quotes = 0;
		*quote_char = '\0';
		return (true);
	}
	return (false);
}

static void	process_removal(t_alloc *alloc, char **item_content_ptr)
{
	char	*src;
	char	*dst;
	char	*new_str;
	char	quote_char;
	int		inside_quotes;

	src = *item_content_ptr;
	new_str = mem_alloc(alloc, str_len(src) + 1);
	dst = new_str;
	inside_quotes = 0;
	quote_char = '\0';
	while (*src)
	{
		if (!handle_quote_state(*src, &quote_char, &inside_quotes))
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
	*dst = '\0';
	*item_content_ptr = new_str;
}

void	quote_removal(t_alloc *alloc, t_token_list *token_list)
{
	char	*token_str;

	while (token_list)
	{
		token_str = token_list->content->str;
		if (str_chr(token_str, '\'') || str_chr(token_str, '"'))
			process_removal(alloc, &token_list->content->str);
		token_list = token_list->next;
	}
}
