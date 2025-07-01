#include "parsing.h"

// TODO -> handle space, tab and \n as the same char in order to handle this
// IFS=$' \t\n', TEST=$' \t word' (because split handle char by char, not the
// whole set)
static void	_execute_split_default(t_alloc *alloc,
	t_token_list *item, char ifs_char)
{
	int				word_index;
	t_token			*token;
	t_token_list	*temp;
	char			**s;

	token = item->content;
	word_index = 0;
	s = str_split(alloc, token->str, ifs_char);
	item->content->str = s[word_index];
	temp = item;
	while (s[++word_index])
	{
		temp->next = (t_token_list *)lst_new(alloc, \
			(void *)new_token(alloc, s[word_index], false, TOK_WORD));
		temp = temp->next;
	}
}

static void	_execute_split_custom(t_alloc *alloc, \
	t_token_list *item, char ifs_char)
{
	t_token			*token;
	t_token_list	*temp;
	char			*str;
	char			*token_str;

	token = item->content;
	token_str = str_dup(alloc, token->str);
	str = str_tok(alloc, &token_str, &ifs_char);
	item->content->str = str;
	temp = item;
	while (token_str != NULL)
	{
		temp->next = (t_token_list *)lst_new(alloc, \
			(void *)new_token(alloc, str_tok(alloc, &token_str, &ifs_char), \
			false, TOK_WORD));
		temp = temp->next;
	}
}

static void	_process_splitting(t_alloc *alloc, t_token_list *item, char *ifs)
{
	t_token			*token;
	size_t			ifs_char_index;

	token = item->content;
	ifs_char_index = 0;
	while (ifs[ifs_char_index])
	{
		if (str_chr(token->str, ifs[ifs_char_index]) != NULL)
		{
			if (str_chr(" \t\n", ifs[ifs_char_index]) != NULL)
				_execute_split_default(alloc, item, ifs[ifs_char_index]);
			else
				_execute_split_custom(alloc, item, ifs[ifs_char_index]);
		}
		ifs_char_index++;
	}
}

void	word_splitting(t_ctx *ctx, t_token_list *token_list)
{
	char			*ifs;
	t_token_list	*current;

	ifs = env_get_var_value(*ctx->env, "IFS");
	if (!ifs)
		ifs = str_dup(*ctx->cmd, " \t\n");
	current = token_list;
	while (current)
	{
		if (current->content->expanded)
			_process_splitting(*ctx->cmd, current, ifs);
		current = current->next;
	}
}
