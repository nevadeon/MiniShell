#include "parsing.h"

static void	_process_removal(t_alloc *alloc, char **item_content_ptr)
{
	char	*original;
	char	*new_str;
	char	*write_ptr;
	int		i;
	int		len;

	original = *item_content_ptr;
	len = str_len(original);
	new_str = mem_alloc(alloc, len + 1);
	write_ptr = new_str;
	i = 0;
	while (original[i])
	{
		if (original[i] != '\'' && original[i] != '"')
		{
			*write_ptr = original[i];
			write_ptr++;
		}
		i++;
	}
	*write_ptr = '\0';
	*item_content_ptr = new_str;
}

void	quote_removal(t_alloc *alloc, t_token_list *token_list)
{
	t_token_list	*current;
	char			*token_str;

	current = token_list;
	while (current)
	{
		token_str = current->content->str;
		if (str_chr(token_str, '\'') || str_chr(token_str, '"'))
			_process_removal(alloc, &current->content->str);
		current = current->next;
	}
}
